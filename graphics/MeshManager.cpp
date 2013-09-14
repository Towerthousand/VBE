#include "MeshManager.hpp"
#include "Mesh.hpp"

std::map<std::string,Mesh*> MeshManager::meshes;

MeshManager::MeshManager() {
}

MeshManager::~MeshManager() {
}

void MeshManager::add(const std::string &meshID, Mesh* mesh) {
	assert(meshes.find(meshID) == meshes.end());
	meshes.insert(std::pair<std::string,Mesh*>(meshID,mesh));
}

Mesh* MeshManager::get(const std::string &meshID) {
	return meshes.at(meshID);
}

void MeshManager::erase(const std::string &meshID) {
	assert(meshes.find(meshID) != meshes.end());
	delete meshes.at(meshID);
	meshes.erase(meshID);
}

void MeshManager::clear() {
	for(std::map<std::string,Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
		delete it->second;
	}
	meshes.clear();
}
