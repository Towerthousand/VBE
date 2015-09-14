#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <iostream>

#include <VBE/graphics/MeshSeparate.hpp>
#include <VBE/geometry/AABB.hpp>

class OBJLoader {
	public:
		static MeshSeparate* loadFromOBJStandard(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType);
		static MeshSeparate* loadFromOBJTangents(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType);

		static void setPositionAttribName(const std::string& name);
		static void setNormalAttribName(const std::string& name);
		static void setTexcoordAttribName(const std::string& name);
		static void setTangentAttribName(const std::string& name);

		static AABB getLastLoadedBoundingBox();
		
	private:
		OBJLoader();
		~OBJLoader();

		static std::string positionAttribName;
		static std::string normalAttribName;
		static std::string texcoordAttribName;
		static std::string tangentAttribName;

		static AABB lastLoadedBBox; //TODO: find a better way to get this...
};

#endif //OBJLOADER_HPP
