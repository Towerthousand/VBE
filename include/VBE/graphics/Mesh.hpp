#ifndef MESH_HPP
#define MESH_HPP

#include <VBE/graphics/MeshSeparate.hpp>

class Mesh final : public MeshSeparate {
    public:
        Mesh();
        Mesh(const Vertex::Format& format, BufferType bufferType = STATIC);

        Mesh(Mesh&& rhs);
        Mesh& operator=(Mesh&& rhs);

        void draw(const ShaderProgram& program) const override;
        void draw(const ShaderProgram& program, unsigned int offset, unsigned int length) const;
        void drawInstanced(const ShaderProgram& program, unsigned int instanceCount) const override;
        void drawInstanced(const ShaderProgram& program, unsigned int instanceCount, unsigned int offset, unsigned int length) const;

        friend void swap(Mesh& a, Mesh& b);
};

#endif // MESH_HPP
