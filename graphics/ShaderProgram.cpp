#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() : programHandle(NULL) {
}

ShaderProgram::~ShaderProgram() {
	if(programHandle != NULL) {
		glDeleteProgram(programHandle);
	}
}

bool ShaderProgram::makeProgram(const std::string &vp_filename, const std::string &fp_filename) {
	outLog("* Loading new vertex shader from " + vp_filename);
	Shader vertex(GL_VERTEX_SHADER);
	vertex.load(vp_filename);
	if (!vertex.compile()) {
		vertex.printInfoLog();
		outLog("#ERROR Compile failed for vertex shader '" + vp_filename + "'.");
		return false;
	}
	else outLog( " - Compiled " + vp_filename + " successfully.");

	outLog("* Loading new fragment shader from " + fp_filename);
	Shader fragment(GL_FRAGMENT_SHADER);
	fragment.load(fp_filename);
	if (!fragment.compile()) {
		fragment.printInfoLog();
		outLog("#ERROR Compile failed for fragment shader '" + fp_filename + "'.");
		return false;
	}
	else outLog( " - Compiled " + fp_filename + " successfully.");

	outLog("* Creating new shaderProgram with " + vp_filename + " and " + fp_filename);
	programHandle = glCreateProgram();
	attachShader(vertex);
	attachShader(fragment);

	if (!link()) {
		printInfoLog();
		outLog("#ERROR Linking program failed!");
		return false;
	}
	else outLog( " - Linked " + vp_filename + " and " + fp_filename + " successfully. PROGRAMID: " + toString(programHandle));

	// Query and store uniforms from the program.
	GLint activeUniforms;
	glGetProgramiv(programHandle, GL_ACTIVE_UNIFORMS, &activeUniforms);
	if (activeUniforms > 0) {
		GLint length;
		glGetProgramiv(programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
		if (length > 0) {
			GLchar uniformName[length + 1];
			GLint uniformSize;
			GLenum uniformType;
			GLint uniformLocation;
			for (int i = 0; i < activeUniforms; ++i) {
				// Query uniform info.
				glGetActiveUniform(programHandle, i, length, NULL, &uniformSize, &uniformType, uniformName);
				uniformName[length] = '\0';  // null terminate
				if (uniformSize > 1 && length > 3) {
					// This is an array uniform. I'm stripping array indexers off it since GL does not
					// seem to be consistent across different drivers/implementations in how it returns
					// array uniforms. On some systems it will return "u_matrixArray", while on others
					// it will return "u_matrixArray[0]".
					char* c = strrchr(uniformName, '[');
					if (c) {
						*c = '\0';
					}
				}

				// Query the pre-assigned uniform location.
				uniformLocation = glGetUniformLocation(programHandle, uniformName);
				Uniform* uniform = new Uniform(uniformSize, uniformLocation);

				uniforms[uniformName] = uniform;
			}
		}
	}
	return true;
}

void ShaderProgram::attachShader(Shader &sh) {
	sh.attach(programHandle);
}

bool ShaderProgram::link() {
	GLint success;
	glLinkProgram(programHandle);
	glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
	return success == GL_TRUE;
}

void ShaderProgram::bind() const {
	glUseProgram(programHandle);
}

void ShaderProgram::unbind() const {
	glUseProgram(0);
}


void ShaderProgram::bindLocation(uint index, const std::string &location) {
	glBindAttribLocation(programHandle, index, (GLchar *)location.c_str());
}

GLint ShaderProgram::getUniLoc(const std::string &uniformID) const {
	return glGetUniformLocation(programHandle, (GLchar *)uniformID.c_str());
}

void ShaderProgram::printInfoLog() {
	int length = 0;
	glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetProgramInfoLog(programHandle, length, NULL, infoLog);
		outLog(infoLog);
	}
}
/////////////////////////////////////////////FLOATS

void ShaderProgram::sendUniform1f(const std::string& uniformID, float x) const {
	bind();
	GLint location = getUniLoc(uniformID);
	if (location == -1) {
		outLog("#ERROR When trying to get uniform: no uniform named " + uniformID);
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
