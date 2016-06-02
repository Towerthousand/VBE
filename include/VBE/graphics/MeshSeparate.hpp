#ifndef MESHSEPARATE_HPP
#define MESHSEPARATE_HPP
#include <VBE/graphics/MeshBase.hpp>

class ShaderBinding;
class ShaderProgram;
class MeshSeparate : public MeshBase {
    public:
        MeshSeparate();
        MeshSeparate(const Vertex::Format& format, BufferType bufferType = STATIC);
        virtual ~MeshSeparate() override;

        void setVertexData(const void* vertexData, unsigned int newVertexCount) override final;
        virtual void bindBuffers() const;
        GLuint getVertexBuffer() const;

        // instancing
        void setInstanceAttribsFormat(const Vertex::Format& format);
        void setInstancesData(const void* instancesData, unsigned int instanceCount);
        const Vertex::Format& getInstanceAttribsFormat() const;
        virtual void bindInstanceDataBuffer() const;
        GLuint getInstanceDataBuffer() const;
        virtual void drawInstanced(const ShaderProgram& program, unsigned int instanceCount) const = 0;

        friend void swap(MeshSeparate& a, MeshSeparate& b);
    protected:
        void setupShaderBinding(const ShaderProgram& program) const;

    private:
        mutable std::map<GLuint, const ShaderBinding*> bindingsCache;
        GLuint vertexBuffer = 0;

        Vertex::Format instanceDataFormat;
        GLuint instanceDataBuffer = 0;
};

#endif // MESHSEPARATE_HPP
