#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "ShaderBinding.hpp"

Mesh::Mesh(Vertex::Format format, BufferType bufferType, bool indexed) :
	vertexFormat(format),
	vertexCount(0),
	indexCount(0),
	vertexBuffer(0),
	primitiveType(TRIANGLES),
	bufferType(bufferType),
	indexed(indexed) {
	GL_ASSERT(glGenBuffers(1, &vertexBuffer), "Failed to create VBO for mesh");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer), "Failed to bind VBO for mesh");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, 0, nullptr, bufferType), "Failed to load VBO with empty vertex data");
	if(indexed) GL_ASSERT(glGenBuffers(1, &indexBuffer), "Failed to create IBO for mesh");
}

Mesh::~Mesh() {
	if(vertexBuffer != 0)
		GL_ASSERT(glDeleteBuffers(1, &vertexBuffer), "Failed to delete VBO");
	for(std::map<GLuint, const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it)
		delete it->second;
}

void Mesh::draw(const ShaderProgram *program) {
	VBE_ASSERT(program->getHandle() != 0, "nullptr program when about to draw mesh");
	GLuint handle = program->getHandle();
	if(bindingsCache.find(handle) == bindingsCache.end())
		bindingsCache.insert(std::pair<GLuint, const ShaderBinding*>(handle, new ShaderBinding(program, this)));
	const ShaderBinding* binding = bindingsCache.at(handle);
	program->use();
	binding->bindVAO();
	if(!indexed) GL_ASSERT(glDrawArrays(primitiveType, 0, vertexCount), "Call to glDrawArrays failed");
	else GL_ASSERT(glDrawElements(primitiveType, indexCount, GL_UNSIGNED_INT, 0), "Call to glDrawElements failed");
}

const Vertex::Format& Mesh::getVertexFormat() const {
	return vertexFormat;
}

unsigned int Mesh::getVertexCount() const {
	return vertexCount;
}

unsigned int Mesh::getVertexSize() const {
	return vertexFormat.vertexSize();
}

Mesh::BufferType Mesh::getType() const {
	return bufferType;
}

GLuint Mesh::getVertexBuffer() const {
	return vertexBuffer;
}

GLuint Mesh::getIndexBuffer() const {
	return indexBuffer;
}

Mesh::PrimitiveType Mesh::getPrimitiveType() const {
	return primitiveType;
}

bool Mesh::isIndexed() const {
	return indexed;
}

void Mesh::setPrimitiveType(Mesh::PrimitiveType type) {
	primitiveType = type;
}

void Mesh::setVertexData(void* vertexData, unsigned int newVertexCount) {
	vertexCount = newVertexCount;
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer), "Failed to bind VBO for mesh");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, vertexData, bufferType), "Failed to send VBO data to GPU");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0), "Failed to bind VBO for mesh");
}

void Mesh::setVertexIndices(unsigned int* indexData, unsigned int newIndexCount) {
	VBE_ASSERT(indexed, "Cannot set indexes for a non-indexed mesh");
	indexCount = newIndexCount;
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer), "Failed to bind IBO for mesh");
	GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indexData, bufferType), "Failed to send IBO data to GPU");
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), "Failed to bind IBO for mesh");
}

struct FunctorComparevec3i{
	bool operator()(const vec3i& a, const vec3i& b)
    {
        if(a.x != b.x) return a.x < b.x;
        if(a.y != b.y) return a.y < b.y;
        if(a.z != b.z) return a.z < b.z;
        return false;
    }
};


Mesh* Mesh::loadFromFile(const std::string filepath, Mesh::BufferType bufferType) {
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
		else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			std::vector<vec3i> vInf(3, vec3i(0));
			char b;
			s   >> vInf[0].x >> b >> vInf[0].y >> b >> vInf[0].z
							 >> vInf[1].x >> b >> vInf[1].y >> b >> vInf[1].z
							 >> vInf[2].x >> b >> vInf[2].y >> b >> vInf[2].z;
			for(unsigned int i = 0; i < 3; ++i)
            {
				std::map<vec3i, int, FunctorComparevec3i>::iterator it = indexMap.find(vInf[i]);
                int ind = 0;
                if(it == indexMap.end())
                {
                    ind = indexMap.size();
					indexMap.insert(std::pair<vec3i, int>(vInf[i], dataIndexed.size()));
					dataIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], textures[vInf[i].y-1]));
                }
                else
                    ind = it->second;

                indices.push_back(ind);

				dataNotIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], textures[vInf[i].y-1]));
            }
		}
	}
	float sizeWithIndex = dataIndexed.size()*sizeof(vert)+indices.size()*sizeof(int);
	float sizeWithoutIndex = dataNotIndexed.size()*sizeof(vert);

	VBE_DLOG(" - Vertex count without indexes: " << dataNotIndexed.size());
	VBE_DLOG(" - Vertex count with indexes: " << dataIndexed.size() << " (" << indices.size() << ") indexes");
	VBE_DLOG(" - Size with indexes: " << sizeWithIndex << ". Size without indexes: " << sizeWithoutIndex);
	Mesh* mesh = nullptr;
	if(sizeWithoutIndex > sizeWithIndex) { //indexed
		mesh = new Mesh(Vertex::Format(elements), bufferType, true);
		mesh->setVertexData(&dataIndexed[0], dataIndexed.size());
		mesh->setVertexIndices(&indices[0], indices.size());
		VBE_DLOG("    Using indexes");
	}
	else { //not indexed
		mesh = new Mesh(Vertex::Format(elements), bufferType, false);
		mesh->setVertexData(&dataNotIndexed[0], dataNotIndexed.size());
		VBE_DLOG("    Not using indexes");
	}
	return mesh;
}

Mesh* Mesh::loadEmpty(Vertex::Format format, Mesh::BufferType bufferType, bool indexed) {
	return new Mesh(format, bufferType, indexed);
}
