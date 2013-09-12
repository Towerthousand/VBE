#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include "../tools.hpp"

class ShaderProgram;
class ShaderManager {
	public:
		static void add(std::string programID,ShaderProgram* program);
		static ShaderProgram* get(std::string programID);
		static void erase(std::string programID);
		static void	clear();
	private:
		static std::map<std::string,ShaderProgram*> programs;
		ShaderManager();
		~ShaderManager();
};


#endif // SHADERMANAGER_HPP
