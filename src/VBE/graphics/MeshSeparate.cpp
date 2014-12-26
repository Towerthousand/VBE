#include <VBE/graphics/MeshSeparate.hpp>
#include <VBE/system/Log.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/graphics/ShaderBinding.hpp>

MeshSeparate::MeshSeparate(const Vertex::Format& format, BufferType bufferType) :
	MeshBase(format, bufferType),
	vertexBuffer(0) {
	GL_ASSERT(glGenBuffers(1, &vertexBuffer));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, 0, nullptr, getBufferType()));
}

MeshSeparate::~MeshSeparate() {
	if(vertexBuffer != 0)
		GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
	for(std::map<GLuint, const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it)
		delete it->second;
}

void swap(MeshSeparate& a, MeshSeparate& b) {
	using std::swap;
	swap(static_cast<MeshBase&>(a), static_cast<MeshBase&>(b));
	swap(a.bindingsCache, b.bindingsCache);
	swap(a.vertexBuffer, b.vertexBuffer);
}

void MeshSeparate::bindBuffers() const {
	VBE_ASSERT(vertexBuffer != 0, "mesh vertex buffer is null");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
}

void MeshSeparate::setupShaderBinding(const ShaderProgram* program) {
	// Get the binding from the cache. If it does not exist, create it.
	GLuint handle = program->getHandle();
	if(bindingsCache.find(handle) == bindingsCache.end())
		bindingsCache.insert(std::pair<GLuint, const ShaderBinding*>(handle, new ShaderBinding(program, this)));
	const ShaderBinding* binding = bindingsCache.at(handle);

	// Bind the program and the binding
	program->use();
	ShaderBinding::bind(binding);
}

GLuint MeshSeparate::getVertexBuffer() const {
	return vertexBuffer;
}

void MeshSeparate::setVertexData(const void* vertexData, unsigned int newVertexCount) {
	// Bind null shader binding, so we don't change the buffer of the previously bound one.
	ShaderBinding::bind(nullptr);
	vertexCount = newVertexCount;
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, getVertexSize() * vertexCount, vertexData, getBufferType()));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
