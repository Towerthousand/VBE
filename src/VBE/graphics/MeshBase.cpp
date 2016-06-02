#include <VBE/graphics/MeshBase.hpp>
#include "ShaderBinding.hpp"

MeshBase::MeshBase() {
}

MeshBase::MeshBase(const Vertex::Format& format, BufferType bufferType)
    : vertexFormat(format),
      bufferType(bufferType) {
}

MeshBase::~MeshBase() {
}

const Vertex::Format& MeshBase::getVertexFormat() const {
    return vertexFormat;
}

unsigned int MeshBase::getVertexCount() const {
    return vertexCount;
}

unsigned int MeshBase::getVertexSize() const {
    return vertexFormat.vertexSize();
}

MeshBase::PrimitiveType MeshBase::getPrimitiveType() const {
    return primitiveType;
}

MeshBase::BufferType MeshBase::getBufferType() const {
    return bufferType;
}

void MeshBase::setPrimitiveType(PrimitiveType type) {
    primitiveType = type;
}

void swap(MeshBase& a, MeshBase& b) {
    using std::swap;
    swap(a.vertexFormat, b.vertexFormat);
    swap(a.vertexCount, b.vertexCount);
    swap(a.primitiveType, b.primitiveType);
    swap(a.bufferType, b.bufferType);
}
