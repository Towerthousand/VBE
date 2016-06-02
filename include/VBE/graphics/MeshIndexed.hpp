#ifndef MESHINDEXED_HPP
#define MESHINDEXED_HPP

#include <VBE/graphics/MeshSeparate.hpp>

class MeshIndexed final : public MeshSeparate {
    public:
        MeshIndexed();
        MeshIndexed(const Vertex::Format& format, BufferType bufferType = STATIC);
        ~MeshIndexed() override;
        MeshIndexed(MeshIndexed&& rhs);
        MeshIndexed& operator=(MeshIndexed&& rhs);

        void bindBuffers() const override;

        void draw(const ShaderProgram& program) const override;
        void draw(const ShaderProgram& program, unsigned int offset, unsigned int length) const;
        void drawInstanced(const ShaderProgram& program, unsigned int instanceCount) const override;
        void drawInstanced(const ShaderProgram& program, unsigned int instanceCount, unsigned int offset, unsigned int length) const;

        GLuint getIndexBuffer() const;
        unsigned int getIndexCount() const;
        void setIndexData(const unsigned int* indexData, unsigned int newIndexCount);

        friend void swap(MeshIndexed& a, MeshIndexed& b);

    private:
        unsigned int indexCount = 0;
        GLuint indexBuffer = 0;
};


#endif // MESHINDEXED_HPP
