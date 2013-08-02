#include "Shader.hpp"

Shader::Shader() {
	shaderHandle = 0;
}

Shader::~Shader() {
}

GLuint& Shader::getHandle() {
	return shaderHandle;
}

bool Shader::loadFromFile(GLenum type, const std::string& filePath) {
	if (shaderHandle) glDeleteShader(shaderHandle);
	shaderHandle = 0;
	//Load
	std::vector<char> fileContents;
	int length;
	if (!getFileContents(filePath,fileContents,length)) {
		outLog("#ERROR Failed to get the contents from " + filePath);
		return false;
	}
	//Create
	shaderHandle = glCreateShader(type);
//	for (int i = 0; i < fileContents.size(); ++i) //output shader
//		std::cout << fileContents[i];
//	std::cout << std::endl;
	GLchar* a[1];
	a[0] = &(fileContents[0]);
	glShaderSource(shaderHandle, 1, (const GLchar**)a, &length);
	//Compile
	glCompileShader(shaderHandle);
	int compiled;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		outLog( "#ERROR Failed to compile: " + filePath);
		int size;
		char buffer[1000];
		glGetShaderInfoLog(shaderHandle, 1000, &size, buffer);
		outLog(buffer);
		glDeleteShader(shaderHandle);
		return false;
	}
	else outLog( " - Compiled " + filePath + " successfully.");
	return true;
}

bool Shader::getFileContents(const std::string& filePath, std::vector<char>& buffer, int &fileLength) {
	std::ifstream file(filePath.c_str(), std::ios_base::binary);
	if (!file)
		return false;
	file.seekg(0, std::ios_base::end);
	fileLength = file.tellg();
	if (fileLength > 0) {
		file.seekg(0, std::ios_base::beg);
		buffer.resize(static_cast<std::size_t>(fileLength));
		file.read(&buffer[0], fileLength);
	}
	buffer.push_back('\0');
	return true;
}
