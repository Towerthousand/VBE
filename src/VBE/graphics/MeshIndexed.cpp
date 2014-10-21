#include <VBE/graphics/MeshIndexed.hpp>
#include <VBE/graphics/ShaderBinding.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/system/Log.hpp>

MeshIndexed::MeshIndexed(const Vertex::Format& format, MeshBase::BufferType bufferType) :
	MeshBase(format, bufferType),
	indexCount(0),
	indexBuffer(0) {
	GL_ASSERT(glGenBuffers(1, &indexBuffer));
}

MeshIndexed::~MeshIndexed() {
	if(indexBuffer != 0)
		GL_ASSERT(glDeleteBuffers(1, &indexBuffer));
}


MeshIndexed::MeshIndexed(MeshIndexed&& rhs) : MeshBase(Vertex::Format(std::vector<Vertex::Element>())) {
	using std::swap;
	swap(*this, rhs);
}

MeshIndexed& MeshIndexed::operator=(MeshIndexed&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}


void MeshIndexed::bindBuffers() const {
	MeshBase::bindBuffers();
	VBE_ASSERT(getIndexBuffer() != 0, "mesh index buffer is null");
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIndexBuffer()));
}

void MeshIndexed::draw(const ShaderProgram *program) {
	VBE_ASSERT(program != nullptr, "program cannot be null");
	VBE_ASSERT(program->getHandle() != 0, "program cannot be null");

	setupShaderBinding(program);

	GL_ASSERT(glDrawElements(getPrimitiveType(), getIndexCount(), GL_UNSIGNED_INT, 0));
}

GLuint MeshIndexed::getIndexBuffer() const {
	return indexBuffer;
}

unsigned int MeshIndexed::getIndexCount() const {
	return indexCount;
}

void MeshIndexed::setIndexData(const unsigned int* indexData, unsigned int newIndexCount) {
	// Bind null shader binding, so we don't change the buffer of the previously bound one.
	ShaderBinding::bind(nullptr);
	indexCount = newIndexCount;
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
	GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, newIndexCount * sizeof(unsigned int), indexData, getBufferType()));
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void swap(MeshIndexed& a, MeshIndexed& b) {
	using std::swap;
	swap(static_cast<MeshBase&>(a), static_cast<MeshBase&>(b));
	swap(a.indexCount, b.indexCount);
	swap(a.indexBuffer, b.indexBuffer);
}
