#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP
#include "../tools.hpp"

class Mesh;
class MeshManager {
	public:
		static void add(std::string meshID,Mesh* mesh);
		static Mesh* get(std::string meshID);
	private:
		static std::map<std::string,Mesh*> meshes;
		MeshManager();
		~MeshManager();
};

#endif // MESHMANAGER_HPP
