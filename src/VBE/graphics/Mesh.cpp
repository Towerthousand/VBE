#include <VBE/graphics/Mesh.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/graphics/ShaderBinding.hpp>
#include <VBE/graphics/OBJLoader.hpp>
#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/system/Log.hpp>

Mesh::Mesh(const Vertex::Format& format, MeshType type, BufferType bufferType) :
	vertexFormat(format),
	vertexCount(0),
	indexCount(0),
	vertexBuffer(0),
	primitiveType(TRIANGLES),
	meshType(type),
	bufferType(bufferType) {
	GL_ASSERT(glGenBuffers(1, &vertexBuffer));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, 0, nullptr, bufferType));
	if(isIndexed()) GL_ASSERT(glGenBuffers(1, &indexBuffer));
}

Mesh::~Mesh() {
	if(vertexBuffer != 0)
		GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
	for(std::map<GLuint, const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it)
		delete it->second;
}

void Mesh::draw(const ShaderProgram *program) {
	draw(program, 0, vertexCount);
}

void Mesh::draw(const ShaderProgram *program, unsigned int offset, unsigned int length) {
    VBE_ASSERT(program->getHandle() != 0, "program cannot be null");
    VBE_ASSERT(length != 0, "length must not be zero");
    VBE_ASSERT(offset < vertexCount, "offset must be smaller than vertex count");
    VBE_ASSERT(offset + length <= vertexCount, "offset plus length must be smaller or equal to vertex count");

    // Get the binding from the cache. If it does not exist, create it.
    GLuint handle = program->getHandle();
    if(bindingsCache.find(handle) == bindingsCache.end())
        bindingsCache.insert(std::pair<GLuint, const ShaderBinding*>(handle, new ShaderBinding(program, this)));
    const ShaderBinding* binding = bindingsCache.at(handle);

    // Bind the program and the binding
    program->use();
    ShaderBinding::bind(binding);
 
	if(isIndexed())
		GL_ASSERT(glDrawElements(primitiveType, indexCount, GL_UNSIGNED_INT, 0));
	else
		GL_ASSERT(glDrawArrays(primitiveType, offset, length));
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
	return meshType == Indexed;
}

void Mesh::setPrimitiveType(Mesh::PrimitiveType type) {
	primitiveType = type;
}

void Mesh::setVertexData(const void* vertexData, unsigned int newVertexCount) {
	ShaderBinding::bind(nullptr);
	vertexCount = newVertexCount;
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, vertexData, bufferType));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Mesh::setVertexIndices(const unsigned int* indexData, unsigned int newIndexCount) {
	ShaderBinding::bind(nullptr);
	VBE_ASSERT(isIndexed(), "Cannot set indexes for a non-indexed mesh");
	indexCount = newIndexCount;
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
	GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indexData, bufferType));
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

Mesh* Mesh::loadFromFile(const std::string filepath, Mesh::BufferType bufferType) {
	return OBJLoader::loadFromOBJTangents(filepath,bufferType);
}

Mesh* Mesh::loadEmpty(const Vertex::Format& format, Mesh::MeshType type, Mesh::BufferType bufferType) {
	return new Mesh(format, type, bufferType);
}
