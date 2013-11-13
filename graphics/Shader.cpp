#include "Shader.hpp"

Shader::Shader(GLenum type) {
	shaderHandle = glCreateShader(type);
}

Shader::~Shader() {
	glDeleteShader(shaderHandle);
}

Shader* Shader::loadShader(const std::string& data, GLenum shaderType) {
	switch(shaderType) {
		case GL_FRAGMENT_SHADER:
			VBE_DLOG("* Loading new fragment shader");
			break;
		case GL_GEOMETRY_SHADER:
			VBE_DLOG("* Loading new geometry shader");
			break;
		case GL_VERTEX_SHADER:
			VBE_DLOG("* Loading new vertex shader");
			break;
		default:
			break;
	}
	Shader* s = new Shader(shaderType);
	s->loadFromString(data);
	s->compile();
	VBE_DLOG(" - Compiled " << out << " successfully.");
	return s;
}

void Shader::loadFromString(const std::string &content) {
	const char* buff = content.c_str();
	const GLint len = content.size();
	glShaderSource(shaderHandle, 1, &buff, &len);
}

void Shader::compile() const {
	GLint status;
	glCompileShader(shaderHandle);
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE) {
		printInfoLog();
		VBE_ASSERT(false, "Compile failed for shader." );
	}
}

void Shader::attach(GLuint program) const {
	VBE_ASSERT(program != 0, "Trying to attach shader with id " << shaderHandle << " to nullptr program");
	glAttachShader(program, shaderHandle);
}

void Shader::printInfoLog() const {
	VBE_ASSERT(shaderHandle != 0, "Trying to query nullptr shader");
	int length = 0;
	glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetShaderInfoLog(shaderHandle, length, nullptr, infoLog);
		VBE_LOG(infoLog );
	}
}
