#ifndef SHADER_HPP
#define SHADER_HPP
#include "tools.hpp"

class Shader {
	public:
		Shader();
		~Shader();
		GLuint &getHandle();
		bool loadFromFile(GLenum type, const std::string &filePath);

	private:
		bool getFileContents(const std::string& filePath, std::vector<char>& buffer, int &fileLength);
		GLuint shaderHandle;
};
#endif // SHADER_HPP
