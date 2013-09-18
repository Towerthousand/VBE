#include "MeshManager.hpp"
#include "Mesh.hpp"

std::map<std::string,Mesh*> MeshManager::meshes;

MeshManager::MeshManager() {
}

MeshManager::~MeshManager() {
}

void MeshManager::add(const std::string &meshID, Mesh* mesh) {
	std::cout << "* Adding mesh with ID " << meshID << std::endl;
	meshes.insert(std::pair<std::string,Mesh*>(meshID,mesh));
}

Mesh* MeshManager::get(const std::string &meshID) {
	return meshes.at(meshID);
}

void MeshManager::erase(const std::string &meshID) {
	std::cout << "* Deleting mesh with ID " << meshID << std::endl;
	delete meshes.at(meshID);
	meshes.erase(meshID);
}

void MeshManager::clear() {
	while(!meshes.empty())
		erase(meshes.begin()->first);
}
