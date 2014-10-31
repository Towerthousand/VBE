#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <iostream>

#include <VBE/graphics/MeshBase.hpp>

class OBJLoader {
	public:
		static MeshBase* loadFromOBJStandard(std::istream& in, Mesh::BufferType bufferType);
		static MeshBase* loadFromOBJTangents(std::istream& in, Mesh::BufferType bufferType);
	private:
		OBJLoader();
		~OBJLoader();
};

#endif //OBJLOADER_HPP
