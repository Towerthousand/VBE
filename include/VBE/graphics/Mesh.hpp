#ifndef MESH_HPP
#define MESH_HPP

#include <VBE/graphics/MeshBase.hpp>

class Mesh : public MeshBase {
	public:
		Mesh(const Vertex::Format& format, MeshBase::BufferType bufferType = STATIC);

		void draw(const ShaderProgram* program) override;
		void draw(const ShaderProgram* program, unsigned int offset, unsigned int length);
};

#endif // MESH_HPP
