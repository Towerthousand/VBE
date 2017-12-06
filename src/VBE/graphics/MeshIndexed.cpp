#include <VBE/graphics/MeshIndexed.hpp>
#include <VBE/graphics/ShaderBinding.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/system/Log.hpp>

MeshIndexed::MeshIndexed() : MeshSeparate() {
}

MeshIndexed::MeshIndexed(const Vertex::Format& format, BufferType bufferType, MeshIndexed::IndexFormat indexFormat) :
    MeshSeparate(format, bufferType) {
    GL_ASSERT(glGenBuffers(1, &indexBuffer));
    this->indexFormat = indexFormat;
}

MeshIndexed::~MeshIndexed() {
    if(indexBuffer != 0)
        GL_ASSERT(glDeleteBuffers(1, &indexBuffer));
}

MeshIndexed::MeshIndexed(MeshIndexed&& rhs) : MeshIndexed() {
    using std::swap;
    swap(*this, rhs);
}

MeshIndexed& MeshIndexed::operator=(MeshIndexed&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void MeshIndexed::bindBuffers() const {
    MeshSeparate::bindBuffers();
    VBE_ASSERT(getIndexBuffer() != 0, "mesh index buffer is null");
    GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIndexBuffer()));
}

void MeshIndexed::draw(const ShaderProgram& program) const {
    draw(program, 0, getIndexCount());
}

void MeshIndexed::draw(const ShaderProgram& program, unsigned int offset, unsigned int length) const {
    VBE_ASSERT(getVertexBuffer() != 0, "Cannot use empty mesh");
    VBE_ASSERT(program.getHandle() != 0, "program cannot be null");

    setupShaderBinding(program);

    switch(indexFormat) {
        case UNSIGNED_INT:
            {
                GL_ASSERT(glDrawElements(getPrimitiveType(), length, indexFormat, (void*)(offset*sizeof(unsigned int))));
                break;
            }
        case UNSIGNED_SHORT:
            {
                GL_ASSERT(glDrawElements(getPrimitiveType(), length, indexFormat, (void*)(offset*sizeof(unsigned short))));
                break;
            }
    }
}

void MeshIndexed::drawInstanced(const ShaderProgram& program, unsigned int instanceCount) const {
    drawInstanced(program, instanceCount, 0, getIndexCount());
}

void MeshIndexed::drawInstanced(const ShaderProgram& program, unsigned int instanceCount, unsigned int offset, unsigned int length) const {
    VBE_ASSERT(getVertexBuffer() != 0, "Cannot use empty mesh");
    VBE_ASSERT(program.getHandle() != 0, "program cannot be null");

    setupShaderBinding(program);

    switch(indexFormat) {
        case UNSIGNED_INT:
            {
                GL_ASSERT(glDrawElementsInstanced(getPrimitiveType(), length, indexFormat, (void*)(offset*sizeof(unsigned int)), instanceCount));
                break;
            }
        case UNSIGNED_SHORT:
            {
                GL_ASSERT(glDrawElementsInstanced(getPrimitiveType(), length, indexFormat, (void*)(offset*sizeof(unsigned short)), instanceCount));
                break;
            }
    }
}


GLuint MeshIndexed::getIndexBuffer() const {
    return indexBuffer;
}

unsigned int MeshIndexed::getIndexCount() const {
    return indexCount;
}

void MeshIndexed::setIndexData(const void* indexData, unsigned int newIndexCount) {
    VBE_ASSERT(getVertexBuffer() != 0, "Cannot use empty mesh");

    // Bind null shader binding, so we don't change the buffer of the previously bound one.
    ShaderBinding::bind(nullptr);
    indexCount = newIndexCount;
    GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
    switch(indexFormat) {
        case UNSIGNED_INT:
            {
                GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, newIndexCount * sizeof(unsigned int), indexData, getBufferType()));
                break;
            }
        case UNSIGNED_SHORT:
            {
                GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, newIndexCount * sizeof(unsigned short), indexData, getBufferType()));
                break;
            }
    }
    GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void swap(MeshIndexed& a, MeshIndexed& b) {
    using std::swap;
    swap(static_cast<MeshSeparate&>(a), static_cast<MeshSeparate&>(b));
    swap(a.indexCount, b.indexCount);
    swap(a.indexBuffer, b.indexBuffer);
    swap(a.indexFormat, b.indexFormat);
}
