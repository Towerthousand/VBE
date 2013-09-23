#include "MeshManager.hpp"
#include "Mesh.hpp"

std::map<std::string,Mesh*> MeshManager::meshes;

MeshManager::MeshManager() {
}

MeshManager::~MeshManager() {
}

void MeshManager::add(const std::string &meshID, Mesh* mesh) {
	VBE_ASSERT(meshes.find(meshID) == meshes.end(), "Failed to add mesh. Mesh " << meshID << " already exists");
	VBE_LOG("* Adding mesh with ID " << meshID );
	meshes.insert(std::pair<std::string,Mesh*>(meshID,mesh));
}

Mesh* MeshManager::get(const std::string &meshID) {
	VBE_ASSERT(meshes.find(meshID) != meshes.end(), "Failed to get mesh. Mesh " << meshID << " doesn't exist");
	return meshes.at(meshID);
}

void MeshManager::erase(const std::string &meshID) {
	VBE_ASSERT(meshes.find(meshID) != meshes.end(), "Failed to delete mesh. Mesh " << meshID << " doesn't exist");
	VBE_LOG("* Deleting mesh with ID " << meshID );
	delete meshes.at(meshID);
	meshes.erase(meshID);
}

void MeshManager::clear() {
	while(!meshes.empty())
		erase(meshes.begin()->first);
}
