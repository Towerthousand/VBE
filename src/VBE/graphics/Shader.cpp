#include <string>

#include <VBE/system/Log.hpp>
#include <VBE/graphics/Shader.hpp>

Shader::Shader(GLenum type) {
	shaderHandle = glCreateShader(type);
	GL_ASSERT({});
	VBE_ASSERT(shaderHandle != 0, "Failed to create shader");
}

Shader::~Shader() {
	GL_ASSERT(glDeleteShader(shaderHandle));
}

Shader* Shader::loadShader(const std::string& data, GLenum shaderType) {
	VBE_DLOG("* Loading new shader");
	Shader* s = new Shader(shaderType);
	s->loadFromString(data);
	s->compile();
	VBE_DLOG(" - Compiled successfully.");
	return s;
}

void Shader::loadFromString(const std::string& content) {
	const char* buff = content.c_str();
	const GLint len = content.size();
	GL_ASSERT(glShaderSource(shaderHandle, 1, &buff, &len));
}

void Shader::compile() const {
	GLint status;
	GL_ASSERT(glCompileShader(shaderHandle));
	GL_ASSERT(glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status));
	if(status != GL_TRUE) {
		printInfoLog();
		VBE_ASSERT(false, "Compile failed for shader." );
	}
}

void Shader::attach(GLuint program) const {
	VBE_ASSERT(program != 0, "Trying to attach shader with id " << shaderHandle << " to nullptr program");
	GL_ASSERT(glAttachShader(program, shaderHandle));
}

void Shader::printInfoLog() const {
	VBE_ASSERT(shaderHandle != 0, "Trying to query nullptr shader");
	int length = 0;
	GL_ASSERT(glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length));
	if (length > 1) {
		GLchar* infoLog = new GLchar[length];
		GL_ASSERT(glGetShaderInfoLog(shaderHandle, length, nullptr, infoLog));
		VBE_LOG(infoLog);
		delete[] infoLog;
	}
}
