#include <VBE/graphics/MeshBase.hpp>
#include <VBE/system/Log.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/graphics/ShaderBinding.hpp>

MeshBase::MeshBase(const Vertex::Format& format, BufferType bufferType) :
	MeshInterface(format, bufferType),
	vertexBuffer(0) {
	GL_ASSERT(glGenBuffers(1, &vertexBuffer));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, 0, nullptr, getBufferType()));
}

MeshBase::~MeshBase() {
	if(vertexBuffer != 0)
		GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
	for(std::map<GLuint, const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it)
		delete it->second;
}

MeshBase::MeshBase(MeshBase&& rhs) : MeshInterface(Vertex::Format(std::vector<Vertex::Element>())) {
	using std::swap;
	swap(*this, rhs);
}

MeshBase& MeshBase::operator=(MeshBase&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}

void MeshBase::bindBuffers() const {
	VBE_ASSERT(vertexBuffer != 0, "mesh vertex buffer is null");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
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

GLuint MeshBase::getVertexBuffer() const {
	return vertexBuffer;
}

void MeshBase::setVertexData(const void* vertexData, unsigned int newVertexCount) {
	// Bind null shader binding, so we don't change the buffer of the previously bound one.
	ShaderBinding::bind(nullptr);
	vertexCount = newVertexCount;
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, getVertexSize() * vertexCount, vertexData, getBufferType()));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void swap(MeshBase& a, MeshBase& b) {
	using std::swap;
	swap(static_cast<MeshInterface&>(a), static_cast<MeshInterface&>(b));
	swap(a.bindingsCache, b.bindingsCache);
	swap(a.vertexBuffer, b.vertexBuffer);
}
