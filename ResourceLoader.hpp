#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP
#include "Manager.hpp"

namespace ResourceLoader {
	Mesh* makeEmptyMesh(Vertex::Format format, Mesh::BufferType bufferType = Mesh::STATIC, bool indexed = false);
	Mesh* makeMeshFromOBJ(const std::string filepath, Mesh::BufferType bufferType = Mesh::STATIC);
}

#endif // RESOURCELOADER_HPP
