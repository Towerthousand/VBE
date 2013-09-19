#include "MeshManager.hpp"
#include "Mesh.hpp"

std::map<std::string,Mesh*> MeshManager::s_meshes;

MeshManager::MeshManager() {
}

MeshManager::~MeshManager() {
}

void MeshManager::add(const std::string &meshID, Mesh* mesh) {
	VBE_ASSERT(s_meshes.find(meshID) == s_meshes.end(), "Failed to add mesh. Mesh " << meshID << " already exists")
	std::cout << "* Adding mesh with ID " << meshID << std::endl;
	s_meshes.insert(std::pair<std::string,Mesh*>(meshID,mesh));
}

Mesh* MeshManager::get(const std::string &meshID) {
	VBE_ASSERT(s_meshes.find(meshID) != s_meshes.end(), "Failed to get mesh. Mesh " << meshID << " doesn't exist")
	return s_meshes.at(meshID);
}

void MeshManager::erase(const std::string &meshID) {
	VBE_ASSERT(s_meshes.find(meshID) != s_meshes.end(), "Failed to delete mesh. Mesh " << meshID << " doesn't exist")
	std::cout << "* Deleting mesh with ID " << meshID << std::endl;
	delete s_meshes.at(meshID);
	s_meshes.erase(meshID);
}

void MeshManager::clear() {
	while(!s_meshes.empty())
		erase(s_meshes.begin()->first);
}
