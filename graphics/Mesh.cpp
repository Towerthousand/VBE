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
	glGenBuffers(1, &vertexBuffer);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to create VBO for mesh");
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to bind VBO for mesh");
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, bufferType);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to load VBO with empty vertex data");
	if(indexed) {
		glGenBuffers(1, &indexBuffer);
		VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to create IBO for mesh");
	}
}

Mesh::~Mesh() {
	if(vertexBuffer != 0)
		glDeleteBuffers(1, &vertexBuffer);
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
	if(!indexed) glDrawArrays(primitiveType, 0, vertexCount);
	else glDrawElements(primitiveType, indexCount, GL_UNSIGNED_INT, 0);
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
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, vertexData, bufferType);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setVertexIndices(unsigned int* indexData, unsigned int newIndexCount) {
	VBE_ASSERT(indexed, "Cannot set indexes for a non-indexed mesh");
	indexCount = newIndexCount;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indexData, bufferType);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	std::vector<unsigned int> indices; //indices into data1
	std::vector<vert> dataIndexed; //indexed data
	std::vector<vert> dataNotIndexed; //unindexed data

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
	VBE_LOG(indices.size());
	float sizeWithIndex = dataIndexed.size()*sizeof(dataIndexed[0])+indices.size()*sizeof(indices[0]);
	float sizeWithoutIndex = dataNotIndexed.size()*sizeof(dataNotIndexed[0]);

	Mesh* mesh = nullptr;
	if(true || sizeWithoutIndex > sizeWithIndex) { //indexed
		mesh = new Mesh(Vertex::Format(elements), bufferType, true);
		mesh->setVertexData(&dataIndexed[0], dataIndexed.size());
		mesh->setVertexIndices(&indices[0], indices.size());
	}
	else { //not indexed
		mesh = new Mesh(Vertex::Format(elements), bufferType, false);
		mesh->setVertexData(&dataNotIndexed[0], dataNotIndexed.size());
	}
	return mesh;
}

Mesh* Mesh::loadEmpty(Vertex::Format format, Mesh::BufferType bufferType, bool indexed) {
	return new Mesh(format, bufferType, indexed);
}
