#ifndef MESH_HPP
#define MESH_HPP

#include <VBE/graphics/MeshSeparate.hpp>

class Mesh final : public MeshSeparate {
	public:
		Mesh();
		Mesh(const Vertex::Format& format, BufferType bufferType = STATIC);
		Mesh(Mesh&& rhs);
		Mesh& operator=(Mesh&& rhs);
		~Mesh();
		friend void swap(Mesh& a, Mesh& b);

		void draw(const ShaderProgram* program) override;
		void draw(const ShaderProgram* program, unsigned int offset, unsigned int length);

};

#endif // MESH_HPP
