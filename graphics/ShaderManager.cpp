#include "ShaderManager.hpp"
#include "ShaderProgram.hpp"

std::map<std::string,ShaderProgram*> ShaderManager::s_programs;

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
}

bool ShaderManager::load(const std::string &programID, const std::string &vert, const std::string &frag) {
	VBE_ASSERT(s_programs.find(programID) == s_programs.end(), "Failed to load program. Program " << programID << " already exists")
	std::cout << "* Loading new ShaderProgram with ID " << programID << " from " << vert << " and " << frag << std::endl;
	ShaderProgram* p = new ShaderProgram();
	if(!p->makeProgram(vert,frag))
		return false;
	s_programs.insert(std::pair<std::string,ShaderProgram*>(programID,p));
	return true;
}

ShaderProgram* ShaderManager::get(const std::string &programID) {
	VBE_ASSERT(s_programs.find(programID) != s_programs.end(), "Failed to get program. Program " << programID << " doesn't exist")
	return s_programs.at(programID);
}

void ShaderManager::erase(const std::string& programID) {
	VBE_ASSERT(s_programs.find(programID) != s_programs.end(), "Failed to erase program. Program " << programID << " doesn't exist")
	std::cout << "* Deleting ShaderProgram with ID " << programID << std::endl;
	delete s_programs.at(programID);
	s_programs.erase(programID);
}

void ShaderManager::clear() {
	while(!s_programs.empty())
		erase(s_programs.begin()->first);
}
