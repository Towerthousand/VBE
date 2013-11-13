#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP
#include "Manager.hpp"

namespace ResourceLoader {
	Mesh* makeEmptyMesh(Vertex::Format format, Mesh::BufferType bufferType = Mesh::STATIC, bool indexed = false);
	Mesh* makeMeshFromOBJ(const std::string filepath, Mesh::BufferType bufferType = Mesh::STATIC);

	ShaderProgram* makeProgramFromString(const std::string &vertSource, const std::string &fragSource);
	ShaderProgram* makeProgramFromString(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);
	ShaderProgram* makeProgramFromFile(const std::string& vp_filename, const std::string& fp_filename);
	ShaderProgram* makeProgramFromFile(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename);

	Texture* makeTextureFromFile(const std::string& filePath, Texture::Format format = Texture::RGBA, bool mipmap = false, int slot = -1);
	Texture* makeTextureFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::Format format = Texture::RGBA, bool mipmap = false, int slot = -1);
}

#endif // RESOURCELOADER_HPP
