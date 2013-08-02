#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() {
	programHandle = 0;
}

ShaderProgram::~ShaderProgram() {
}

bool ShaderProgram::makeProgram(const std::string& filePathVertex, const std::string& filePathFragment) {
	if (programHandle != 0) glDeleteProgram(programHandle);
	programHandle = 0;
	outLog("* Loading new vertex shader from " + filePathVertex);
	if (!vertex.loadFromFile(GL_VERTEX_SHADER,filePathVertex))
		return false;
	outLog("* Loading new fragment shader from " + filePathFragment);
	if (!fragment.loadFromFile(GL_FRAGMENT_SHADER,filePathFragment))
		return false;
	outLog("* Creating new shader program");
	GLint linked;
	programHandle = glCreateProgram();
	glAttachShader(programHandle, vertex.getHandle());
	glAttachShader(programHandle, fragment.getHandle());
	glLinkProgram(programHandle);
	glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
	if (!linked) {
		outLog("#ERROR Failed to link shader program");
		int size;
		char buffer[1000];
		glGetProgramInfoLog(programHandle, 1000, &size, buffer);
		outLog(buffer);
		glDeleteProgram(programHandle);
		return false;
	}
	name = filePathVertex + filePathFragment;
	return true;
}

void ShaderProgram::use() const {
	glUseProgram(programHandle);
}

void ShaderProgram::bindLocation(uint index, const std::string &location) {
	glBindAttribLocation(programHandle, index, (GLchar *)location.c_str());
}

GLint ShaderProgram::getUniLoc(const std::string &uniformID) const {
	return glGetUniformLocation(programHandle, (GLchar *) uniformID.c_str());
}

/////////////////////////////////////////////FLOATS

void ShaderProgram::sendUniform1f(const std::string& uniformID, float x) const {
	use();
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID +" " + name);
		return;
	}
	glUniform1f(location, x);
}

void ShaderProgram::sendUniform2f(const std::string& uniformID
						   , float x, float y) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform2f(location, x, y);
}

void ShaderProgram::sendUniform2f(const std::string& uniformID, const vec2f& v) const {
	sendUniform2f(uniformID, v.x, v.y);
}

void ShaderProgram::sendUniform3f(const std::string& uniformID
						   , float x, float y, float z) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform3f(location, x, y, z);
}

void ShaderProgram::sendUniform3f(const std::string& uniformID, const vec3f& v) const {
	sendUniform3f(uniformID, v.x, v.y, v.z);
}

void ShaderProgram::sendUniform4f(const std::string& uniformID
						   , float x, float y, float z, float w) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform4f(location, x, y, z, w);
}

void ShaderProgram::sendUniform4f(const std::string& uniformID, const vec4f& v) const {
	sendUniform4f(uniformID, v.x, v.y, v.z, v.w);
}

/////////////////////////////////////////////INTEGERS

void ShaderProgram::sendUniform1i(const std::string& uniformID, int x) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform1i(location, x);
}

void ShaderProgram::sendUniform2i(const std::string& uniformID
						   , int x, int y) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform2i(location, x, y);
}

void ShaderProgram::sendUniform2i(const std::string& uniformID, const vec2i& v) const {
	sendUniform2i(uniformID, v.x, v.y);
}

void ShaderProgram::sendUniform3i(const std::string& uniformID
						   , int x, int y, int z) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform3i(location, x, y, z);
}

void ShaderProgram::sendUniform3i(const std::string& uniformID, const vec3i& v) const {
	sendUniform3i(uniformID, v.x, v.y, v.z);
}

void ShaderProgram::sendUniform4i(const std::string& uniformID
						   , int x, int y, int z, int w) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform4i(location, x, y, z, w);
}

void ShaderProgram::sendUniform4i(const std::string& uniformID, const vec4i& v) const {
	sendUniform4i(uniformID, v.x, v.y, v.z, v.w);
}

/////////////////////////////////////////////UNSIGNED INTEGERS

void ShaderProgram::sendUniform1ui(const std::string& uniformID, uint x) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform1ui(location, x);
}

void ShaderProgram::sendUniform2ui(const std::string& uniformID
							, uint x, uint y) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform2ui(location, x, y);
}

void ShaderProgram::sendUniform2ui(const std::string& uniformID, const vec2ui& v) const {
	sendUniform2ui(uniformID, v.x, v.y);
}

void ShaderProgram::sendUniform3ui(const std::string& uniformID
							, uint x, uint y, uint z) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform3ui(location, x, y, z);
}

void ShaderProgram::sendUniform3ui(const std::string& uniformID, const vec3ui& v) const {
	sendUniform3ui(uniformID, v.x, v.y, v.z);
}

void ShaderProgram::sendUniform4ui(const std::string& uniformID
							, uint x, uint y, uint z, uint w) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniform4ui(location, x, y, z, w);
}

void ShaderProgram::sendUniform4ui(const std::string& uniformID, const vec4ui& v) const {
	sendUniform4ui(uniformID, v.x, v.y, v.z, v.w);
}

/////////////////////////////////////////////MATRIX

void ShaderProgram::sendUniformMat2f(const std::string& uniformID
							  , const mat2f &mat) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::sendUniformMat3f(const std::string& uniformID
							  , const mat3f &mat) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::sendUniformMat4f(const std::string& uniformID
							  , const mat4f &mat) const {
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}
