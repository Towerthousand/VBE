#include "Shader.hpp"

Shader::Shader(GLenum type) {
	m_shaderHandle = glCreateShader(type);
}

Shader::~Shader() {
	glDeleteShader(m_shaderHandle);
}

bool Shader::load(const std::string &filename) {
	std::ifstream is;
	is.open(filename, std::ios::in);
	if (is.fail()) {
		std::cout << "#ERROR Failed to get the contents from " << filename << std::endl;
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
	glShaderSource(m_shaderHandle, 1, &source, NULL);

	return true;
}

bool Shader::compile() const {
	GLint status;
	glCompileShader(m_shaderHandle);
	glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

void Shader::attach(GLuint program) const {
	VBE_ASSERT(program != 0, "Trying to attach shader with id " << m_shaderHandle << " to null program")
	glAttachShader(program, m_shaderHandle);
}

void Shader::printInfoLog() const {
	VBE_ASSERT(m_shaderHandle != 0, "Trying to query null shader")
	int length = 0;
	glGetShaderiv(m_shaderHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetShaderInfoLog(m_shaderHandle, length, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
}
