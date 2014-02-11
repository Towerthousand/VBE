#include "Shader.hpp"

Shader::Shader(GLenum type) {
	shaderHandle = glCreateShader(type);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to create shader");
}

Shader::~Shader() {
	GL_ASSERT(glDeleteShader(shaderHandle), "Failed to delete shader");
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
	VBE_DLOG(" - Compiled successfully.");
	return s;
}

void Shader::loadFromString(const std::string &content) {
	const char* buff = content.c_str();
	const GLint len = content.size();
	GL_ASSERT(glShaderSource(shaderHandle, 1, &buff, &len),"Failed to set shader source");
}

void Shader::compile() const {
	GLint status;
	GL_ASSERT(glCompileShader(shaderHandle),"Failed to execute compilation for shader");
	GL_ASSERT(glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status),"Failed glGetShaderiv");
	if(status != GL_TRUE) {
		printInfoLog();
		VBE_ASSERT(false, "Compile failed for shader." );
	}
}

void Shader::attach(GLuint program) const {
	VBE_ASSERT(program != 0, "Trying to attach shader with id " << shaderHandle << " to nullptr program");
	GL_ASSERT(glAttachShader(program, shaderHandle), "Failed to attach shader");
}

void Shader::printInfoLog() const {
	VBE_ASSERT(shaderHandle != 0, "Trying to query nullptr shader");
	int length = 0;
	GL_ASSERT(glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length), "Failed glGetShaderiv");
	if (length > 1) {
		GLchar* infoLog = new GLchar[length];
		GL_ASSERT(glGetShaderInfoLog(shaderHandle, length, nullptr, infoLog), "Failed glGetShaderInfoLog");
		VBE_LOG(infoLog);
		delete[] infoLog;
	}
}
