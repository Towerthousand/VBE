#include "MeshManager.hpp"

std::map<std::string,Mesh*> MeshManager::meshes;

MeshManager::MeshManager() {
}

MeshManager::~MeshManager() {
}

void MeshManager::add(std::string meshID,Mesh* mesh) {
	assert(meshes.find(meshID) == meshes.end());
	meshes.insert(std::pair<std::string,Mesh*>(meshID,mesh));
}

Mesh* MeshManager::get(std::string meshID) {
	return meshes.at(meshID);
}
