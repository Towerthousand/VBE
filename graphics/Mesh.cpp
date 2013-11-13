#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "ShaderBinding.hpp"

Mesh::Mesh(BufferType bufferType, bool indexed) :
	vertexFormat(std::vector<Vertex::Element>()),
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
		glDeleteBuffers(1,&vertexBuffer);
	for(std::map<GLuint,const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it)
		delete it->second;
}

void Mesh::draw(const ShaderProgram *program) {
	VBE_ASSERT(program->getHandle() != 0, "nullptr program when about to draw mesh");
	GLuint handle = program->getHandle();
	if(bindingsCache.find(handle) == bindingsCache.end())
		bindingsCache.insert(std::pair<GLuint,const ShaderBinding*>(handle,new ShaderBinding(program, this)));
	const ShaderBinding* binding = bindingsCache.at(handle);
	program->use();
	binding->bindVAO();
	if(!indexed) glDrawArrays(primitiveType, 0, vertexCount);
	else glDrawElements(primitiveType, indexCount, GL_UNSIGNED_SHORT, 0);
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

void Mesh::setVertexFormat(const Vertex::Format& format) {
	vertexFormat = format;
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

void Mesh::setVertexIndices(unsigned short* indexData, unsigned int newIndexCount) {
	VBE_ASSERT(indexed, "Cannot set indexes for a non-indexed mesh");
	indexCount = newIndexCount;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indexData, bufferType);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
