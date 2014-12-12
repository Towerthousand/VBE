#include <VBE/graphics/Mesh.hpp>
#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/system/Log.hpp>

Mesh::Mesh() : Mesh(Vertex::Format()) {

}

Mesh::Mesh(const Vertex::Format& format, MeshBase::BufferType bufferType) :
	MeshBase(format, bufferType) {
}

Mesh::Mesh(Mesh&& rhs) : Mesh(Vertex::Format(std::vector<Vertex::Element>())){
	using std::swap;
	swap(*this, rhs);
}

Mesh& Mesh::operator=(Mesh&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}

void Mesh::draw(const ShaderProgram* program) {
	draw(program, 0, getVertexCount());
}

void Mesh::draw(const ShaderProgram* program, unsigned int offset, unsigned int length) {
	VBE_ASSERT(program != nullptr, "program cannot be null");
	VBE_ASSERT(program->getHandle() != 0, "program cannot be null");
	VBE_ASSERT(length != 0, "length must not be zero");
	VBE_ASSERT(offset < getVertexCount(), "offset must be smaller than vertex count");
	VBE_ASSERT(offset + length <= getVertexCount(), "offset plus length must be smaller or equal to vertex count");

	setupShaderBinding(program);

	GL_ASSERT(glDrawArrays(getPrimitiveType(), offset, length));
}

void swap(Mesh& a, Mesh& b) {
	using std::swap;
	swap(static_cast<MeshBase&>(a), static_cast<MeshBase&>(b));
}
