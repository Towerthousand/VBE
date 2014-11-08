#include <VBE/graphics/MeshInterface.hpp>

MeshInterface::MeshInterface(const Vertex::Format& format, BufferType bufferType)
	: vertexFormat(format),
	  vertexCount(0),
	  primitiveType(TRIANGLES),
	  bufferType(bufferType) {
}

MeshInterface::~MeshInterface() {
}

const Vertex::Format&MeshInterface::getVertexFormat() const {
	return vertexFormat;
}

unsigned int MeshInterface::getVertexCount() const {
	return vertexCount;
}

unsigned int MeshInterface::getVertexSize() const {
	return vertexFormat.vertexSize();
}

MeshInterface::PrimitiveType MeshInterface::getPrimitiveType() const {
	return primitiveType;
}

MeshInterface::BufferType MeshInterface::getBufferType() const {
	return bufferType;
}

void MeshInterface::setPrimitiveType(PrimitiveType type) {
	primitiveType = type;
}

void swap(MeshInterface& a, MeshInterface& b) {
	using std::swap;
	swap(a.vertexFormat, b.vertexFormat);
	swap(a.vertexCount, b.vertexCount);
	swap(a.primitiveType, b.primitiveType);
	swap(a.bufferType, b.bufferType);
}
