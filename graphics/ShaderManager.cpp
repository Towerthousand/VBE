#include "ShaderManager.hpp"
#include "ShaderProgram.hpp"

std::map<std::string,ShaderProgram*> ShaderManager::programs;

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
}

bool ShaderManager::load(const std::string &programID, const std::string &vert, const std::string &frag) {
	VBE_ASSERT(programs.find(programID) == programs.end(), "Failed to load program. Program " << programID << " already exists");
	VBE_LOG("* Loading new ShaderProgram with ID " << programID << " from " << vert << " and " << frag );
	ShaderProgram* p = new ShaderProgram();
	if(!p->makeProgram(vert,frag))
		return false;
	programs.insert(std::pair<std::string,ShaderProgram*>(programID,p));
	return true;
}

ShaderProgram* ShaderManager::get(const std::string &programID) {
	VBE_ASSERT(programs.find(programID) != programs.end(), "Failed to get program. Program " << programID << " doesn't exist");
	return programs.at(programID);
}

void ShaderManager::erase(const std::string& programID) {
	VBE_ASSERT(programs.find(programID) != programs.end(), "Failed to erase program. Program " << programID << " doesn't exist");
	VBE_LOG("* Deleting ShaderProgram with ID " << programID );
	delete programs.at(programID);
	programs.erase(programID);
}

void ShaderManager::clear() {
	while(!programs.empty())
		erase(programs.begin()->first);
}
