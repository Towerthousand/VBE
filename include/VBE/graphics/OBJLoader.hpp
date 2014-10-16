#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>

#include <VBE/graphics/Mesh.hpp>

class OBJLoader {
	public:
		static Mesh* loadFromOBJStandard(const std::string& filepath, Mesh::BufferType bufferType);
		static Mesh* loadFromOBJTangents(const std::string& filepath, Mesh::BufferType bufferType);
	private:
		OBJLoader();
		~OBJLoader();
};

#endif //OBJLOADER_HPP
