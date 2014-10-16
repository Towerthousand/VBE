#include "OBJLoader.hpp"

struct FunctorComparevec3i{
		bool operator()(const vec3i& a, const vec3i& b) {
			if(a.x != b.x) return a.x < b.x;
			if(a.y != b.y) return a.y < b.y;
			if(a.z != b.z) return a.z < b.z;
			return false;
		}
};

Mesh* OBJLoader::loadFromOBJStandard(const std::string& filepath, Mesh::BufferType bufferType) {
	VBE_DLOG("* Loading new OBJ from path " << filepath << ". Expected format: V/T/N");
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Normal   , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

	struct vert {
			vert(vec3f pos, vec3f nor, vec2f tex) : pos(pos) , nor(nor), tex(tex) {}
			vec3f pos, nor;
			vec2f tex;
	};

	std::ifstream in(filepath.c_str(), std::ifstream::in);
	VBE_ASSERT(in, "While importing OBJ: Cannot open " << filepath );

	std::vector<vec3f> vertices;
	std::vector<vec3f> normals;
	std::vector<vec2f> textures;
	std::vector<unsigned int> indices;
	std::vector<vert> dataIndexed;
	std::vector<vert> dataNotIndexed;
	std::map<vec3i, int, FunctorComparevec3i> indexMap;

	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			vec3f v;
			s >> v.x >> v.y >> v.z;
            vertices.push_back(v);
		}
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream s(line.substr(3));
			vec3f v;
			s >> v.x >> v.y >> v.z;
			normals.push_back(v);
		}
		else if (line.substr(0, 3) == "vt ") {
			std::istringstream s(line.substr(3));
			vec2f v;
			s >> v.x >> v.y;
			v.y = 1-v.y;
			textures.push_back(v);
		}
		//f 1/1/1 2/2/2 3/3/3
		else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			std::vector<vec3i> vInf(3, vec3i(0));
			char b;
			s   >> vInf[0].x >> b >> vInf[0].y >> b >> vInf[0].z
							 >> vInf[1].x >> b >> vInf[1].y >> b >> vInf[1].z
							 >> vInf[2].x >> b >> vInf[2].y >> b >> vInf[2].z;
			for(unsigned int i = 0; i < 3; ++i) {
				std::map<vec3i, int, FunctorComparevec3i>::iterator it = indexMap.find(vInf[i]);
				int ind = 0;
				if(it == indexMap.end()) {
					ind = indexMap.size();
					indexMap.insert(std::pair<vec3i, int>(vInf[i], dataIndexed.size()));
					dataIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], textures[vInf[i].y-1]));
				}
				else ind = it->second;
				indices.push_back(ind);
				dataNotIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], textures[vInf[i].y-1]));
			}
		}
	}
	int sizeWithIndex = dataIndexed.size()*sizeof(vert)+indices.size()*sizeof(int);
	int sizeWithoutIndex = dataNotIndexed.size()*sizeof(vert);

	VBE_DLOG(" - Vertex count without indexes: " << dataNotIndexed.size());
	VBE_DLOG(" - Vertex count with indexes: " << dataIndexed.size() << " (" << indices.size() << ") indexes");
	VBE_DLOG(" - Size with indexes: " << sizeWithIndex << ". Size without indexes: " << sizeWithoutIndex);
	Mesh* mesh = nullptr;
    if(sizeWithoutIndex > sizeWithIndex) { //indexed
        mesh = Mesh::loadEmpty(Vertex::Format(elements), bufferType, true);
		mesh->setVertexData(&dataIndexed[0], dataIndexed.size());
		mesh->setVertexIndices(&indices[0], indices.size());
		VBE_DLOG("    Using indexes");
	}
    else { //not indexed
        mesh = Mesh::loadEmpty(Vertex::Format(elements), bufferType, false);
		mesh->setVertexData(&dataNotIndexed[0], dataNotIndexed.size());
		VBE_DLOG("    Not using indexes");
    }
	return mesh;
}

Mesh* OBJLoader::loadFromOBJTangents(const std::string& filepath, Mesh::BufferType bufferType) {
	VBE_DLOG("* Loading new OBJ from path " << filepath << ". Expected format: V/T/N");
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Normal   , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::get("a_tangent") , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

	struct vert {
			vert(vec3f pos, vec3f nor, vec3f tan, vec2f tex) : pos(pos) , nor(nor), tan(tan), tex(tex) {}
			vec3f pos, nor, tan;
			vec2f tex;
	};

	std::ifstream in(filepath.c_str(), std::ifstream::in);
	VBE_ASSERT(in, "While importing OBJ: Cannot open " << filepath );

	std::vector<vec3f> vertices;
	std::vector<vec3f> normals;
	std::vector<vec3f> tangents;
	std::vector<vec2f> textures;
	std::vector<unsigned int> indices;
	std::vector<vert> dataIndexed;
	std::vector<vert> dataNotIndexed;
	std::map<vec3i, int, FunctorComparevec3i> indexMap;

	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			vec3f v;
			s >> v.x >> v.y >> v.z;
            vertices.push_back(v);
		}
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream s(line.substr(3));
			vec3f v;
			s >> v.x >> v.y >> v.z;
			normals.push_back(v);
			vec3f t = glm::cross(glm::normalize(v), vec3f(0, 0, 1));
			if (glm::length(t) < 0.01) t = glm::cross(glm::normalize(v), vec3f(0, 1, 0));
			tangents.push_back(t);
		}
		else if (line.substr(0, 3) == "vt ") {
			std::istringstream s(line.substr(3));
			vec2f v;
			s >> v.x >> v.y;
			v.y = 1-v.y;
			textures.push_back(v);
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			std::vector<vec3i> vInf(3, vec3i(0));
			char b;
			s   >> vInf[0].x >> b >> vInf[0].y >> b >> vInf[0].z
							 >> vInf[1].x >> b >> vInf[1].y >> b >> vInf[1].z
							 >> vInf[2].x >> b >> vInf[2].y >> b >> vInf[2].z;
			for(unsigned int i = 0; i < 3; ++i) {
				std::map<vec3i, int, FunctorComparevec3i>::iterator it = indexMap.find(vInf[i]);
				int ind = 0;
				if(it == indexMap.end()) {
					ind = indexMap.size();
					indexMap.insert(std::pair<vec3i, int>(vInf[i], dataIndexed.size()));
					dataIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], tangents[vInf[i].z-1], textures[vInf[i].y-1]));
				}
				else ind = it->second;
				indices.push_back(ind);
				dataNotIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], tangents[vInf[i].z-1], textures[vInf[i].y-1]));
			}
		}
	}
	int sizeWithIndex = dataIndexed.size()*sizeof(vert)+indices.size()*sizeof(int);
	int sizeWithoutIndex = dataNotIndexed.size()*sizeof(vert);

	VBE_DLOG(" - Vertex count without indexes: " << dataNotIndexed.size());
	VBE_DLOG(" - Vertex count with indexes: " << dataIndexed.size() << " (" << indices.size() << ") indexes");
	VBE_DLOG(" - Size with indexes: " << sizeWithIndex << ". Size without indexes: " << sizeWithoutIndex);
	Mesh* mesh = nullptr;
	if(sizeWithoutIndex > sizeWithIndex) { //indexed
        mesh = Mesh::loadEmpty(Vertex::Format(elements), bufferType, true);
		mesh->setVertexData(&dataIndexed[0], dataIndexed.size());
		mesh->setVertexIndices(&indices[0], indices.size());
		VBE_DLOG("    Using indexes");
	}
	else { //not indexed
        mesh = Mesh::loadEmpty(Vertex::Format(elements), bufferType, false);
		mesh->setVertexData(&dataNotIndexed[0], dataNotIndexed.size());
		VBE_DLOG("    Not using indexes");
    }
	return mesh;
}
