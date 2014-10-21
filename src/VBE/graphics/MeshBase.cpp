#include <VBE/graphics/MeshBase.hpp>
#include <VBE/system/Log.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/graphics/ShaderBinding.hpp>

MeshBase::MeshBase(const Vertex::Format& format, BufferType bufferType) :
	vertexFormat(format),
	vertexCount(0),
	vertexBuffer(0),
	primitiveType(TRIANGLES),
	bufferType(bufferType) {
	GL_ASSERT(glGenBuffers(1, &vertexBuffer));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, 0, nullptr, bufferType));
}

MeshBase::~MeshBase() {
	if(vertexBuffer != 0)
		GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
	for(std::map<GLuint, const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it)
		delete it->second;
}

void MeshBase::bindBuffers() const {
	VBE_ASSERT(getVertexBuffer() != 0, "mesh vertex buffer is null");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, getVertexBuffer()));
}

void MeshBase::setupShaderBinding(const ShaderProgram* program) {
	// Get the binding from the cache. If it does not exist, create it.
	GLuint handle = program->getHandle();
	if(bindingsCache.find(handle) == bindingsCache.end())
		bindingsCache.insert(std::pair<GLuint, const ShaderBinding*>(handle, new ShaderBinding(program, this)));
	const ShaderBinding* binding = bindingsCache.at(handle);

	// Bind the program and the binding
	program->use();
	ShaderBinding::bind(binding);
}


const Vertex::Format& MeshBase::getVertexFormat() const {
	return vertexFormat;
}

unsigned int MeshBase::getVertexCount() const {
	return vertexCount;
}

unsigned int MeshBase::getVertexSize() const {
	return vertexFormat.vertexSize();
}

GLuint MeshBase::getVertexBuffer() const {
	return vertexBuffer;
}

MeshBase::PrimitiveType MeshBase::getPrimitiveType() const {
	return primitiveType;
}

MeshBase::BufferType MeshBase::getBufferType() const {
	return bufferType;
}

void MeshBase::setPrimitiveType(MeshBase::PrimitiveType type) {
	primitiveType = type;
}

void MeshBase::setVertexData(const void* vertexData, unsigned int newVertexCount) {
	// Bind null shader binding, so we don't change the buffer of the previously bound one.
	ShaderBinding::bind(nullptr);
	vertexCount = newVertexCount;
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, vertexData, bufferType));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
