#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#include "../tools.hpp"

class ShaderProgram;
class ShaderManager {
	public:
		static bool load(const std::string& programID, const std::string& vert, const std::string& frag);
		static ShaderProgram* get(const std::string& programID);
		static void erase(const std::string& programID);
		static void	clear();
	private:
		static std::map<std::string,ShaderProgram*> programs;
		ShaderManager();
		~ShaderManager();
};


#endif // SHADERMANAGER_HPP
