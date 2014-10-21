#ifndef MESH_HPP
#define MESH_HPP

#include <VBE/graphics/MeshBase.hpp>

class Mesh : public MeshBase {
	public:
		Mesh(const Vertex::Format& format, MeshBase::BufferType bufferType = STATIC);

		Mesh(Mesh&& rhs);
		Mesh& operator=(Mesh&& rhs);

		void draw(const ShaderProgram* program) override;
		void draw(const ShaderProgram* program, unsigned int offset, unsigned int length);

		friend void swap(Mesh& a, Mesh& b);
};

#endif // MESH_HPP
