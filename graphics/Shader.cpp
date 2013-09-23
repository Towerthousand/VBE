#include "Shader.hpp"

Shader::Shader(GLenum type) {
	shaderHandle = glCreateShader(type);
}

Shader::~Shader() {
	glDeleteShader(shaderHandle);
}

bool Shader::load(const std::string &filename) {
	std::ifstream is;
	is.open(filename, std::ios::in);
	if (is.fail()) {
		VBE_LOG("#ERROR Failed to get the contents from " << filename );
		return false;
	}

	// get length of file
	is.seekg(0, std::ios::end);
	int length = (int) is.tellg();
	is.seekg(0, std::ios::beg);

	// allocate memory:
	char buffer[length+1];

	// read data as a block:
	is.read(buffer, length);
	is.close();

	buffer[length] = '\0';
	const char *source = buffer;
	glShaderSource(shaderHandle, 1, &source, NULL);

	return true;
}

bool Shader::compile() const {
	GLint status;
	glCompileShader(shaderHandle);
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

void Shader::attach(GLuint program) const {
	VBE_ASSERT(program != 0, "Trying to attach shader with id " << shaderHandle << " to null program");
	glAttachShader(program, shaderHandle);
}

void Shader::printInfoLog() const {
	VBE_ASSERT(shaderHandle != 0, "Trying to query null shader");
	int length = 0;
	glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetShaderInfoLog(shaderHandle, length, NULL, infoLog);
		VBE_LOG(infoLog );
	}
}
