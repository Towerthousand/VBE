#include "ShaderProgram.hpp"
#include "Uniform.hpp"

std::map<std::string,ShaderProgram*> ShaderProgram::programs;

ShaderProgram::ShaderProgram() : programHandle(0) {
}

ShaderProgram::~ShaderProgram() {
	if(programHandle != 0) {
		glDeleteProgram(programHandle);
	}
}

bool ShaderProgram::makeProgram(const std::string &vp_filename, const std::string &fp_filename) {
	std::cout << "* Loading new vertex shader from " << vp_filename << std::endl;;
	Shader vertex(GL_VERTEX_SHADER);
	vertex.load(vp_filename);
	if (!vertex.compile()) {
		vertex.printInfoLog();
		std::cout << "#ERROR Compile failed for vertex shader '" << vp_filename << "'." << std::endl;;
		return false;
	}
	else std::cout << " - Compiled " << vp_filename << " successfully." << std::endl;;

	std::cout << "* Loading new fragment shader from " << fp_filename << std::endl;;
	Shader fragment(GL_FRAGMENT_SHADER);
	fragment.load(fp_filename);
	if (!fragment.compile()) {
		fragment.printInfoLog();
		std::cout << "#ERROR Compile failed for fragment shader '" << fp_filename << "'." << std::endl;
		return false;
	}
	else std::cout <<  " - Compiled " << fp_filename << " successfully." << std::endl;

	std::cout << "* Creating new shaderProgram with " << vp_filename << " and " << fp_filename << std::endl;
	programHandle = glCreateProgram();
	attachShader(vertex);
	attachShader(fragment);

	if (!link()) {
		printInfoLog();
		std::cout << "#ERROR Linking program failed!" << std::endl;
		return false;
	}
	else std::cout <<  " - Linked " << vp_filename << " and " << fp_filename << " successfully. PROGRAMID: " << programHandle << std::endl;
	std::cout << "--------------" << std::endl;
	// Query and store vertex attribute meta-data from the program
	GLint activeAttributes;
	glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
	if (activeAttributes > 0) {
		GLint length;
		glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
		if (length > 0) {
			GLchar attribName[length + 1];
			GLint attribSize;
			GLenum attribType;
			GLint attribLocation;
			for (int i = 0; i < activeAttributes; ++i) {
				// Query attribute info.
				glGetActiveAttrib(programHandle, i, length, NULL, &attribSize, &attribType, attribName);
				attribName[length] = '\0';

				// Query the pre-assigned attribute location.
				attribLocation = glGetAttribLocation(programHandle, attribName);

				// Assign the vertex attribute mapping for the effect.
				attributes[attribName] = attribLocation;
			}
		}
	}

	std::cout << "Printing attribute info:" << std::endl;
	for(std::map<std::string,GLint>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
		std::cout << it->first << " at location " << it->second << std::endl;
	}

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
				Uniform* uniform = new Uniform(uniformSize, uniformType, uniformLocation);

				uniforms[uniformName] = uniform;
			}
		}
	}
	std::cout << "Printing uniform info:" << std::endl;
	for(std::map<std::string,Uniform*>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
		std::cout << it->first << ":" << std::endl;
		it->second->log();
	}
	std::cout << "--------------" << std::endl;
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

void ShaderProgram::printInfoLog() {
	int length = 0;
	glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetProgramInfoLog(programHandle, length, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
}

void ShaderProgram::add(std::string name, ShaderProgram *program) {
	ShaderProgram::programs.insert(std::pair<std::string,ShaderProgram*>(name,program));
}

ShaderProgram* ShaderProgram::get(std::string name){
	return ShaderProgram::programs.at(name);
}

void ShaderProgram::sendUniformMat4f(const std::string& uniformID
									 , const mat4f &mat) const {
	GLint location = glGetUniformLocation(programHandle, (GLchar *)uniformID.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}
