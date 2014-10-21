#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>

#include <VBE/graphics/MeshBase.hpp>

class OBJLoader {
	public:
		static MeshBase* loadFromOBJStandard(const std::string& filepath, Mesh::BufferType bufferType);
		static MeshBase* loadFromOBJTangents(const std::string& filepath, Mesh::BufferType bufferType);
	private:
		OBJLoader();
		~OBJLoader();
};

#endif //OBJLOADER_HPP
