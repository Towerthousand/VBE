#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP
#include "tools.hpp"

class Mesh;
class OBJLoader {
	public:
		Mesh loadFromOBJStandard(const std::string& filePath);
		Mesh loadFromOBJTangentsBitangents(const std::string& filePath);
	private:
		OBJLoader();
		~OBJLoader();
}

#endif //OBJLOADER_HPP
