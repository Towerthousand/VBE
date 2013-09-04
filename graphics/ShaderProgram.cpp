#include "ShaderProgram.hpp"
#include "Uniform.hpp"

std::map<std::string,ShaderProgram*> ShaderProgram::programs;
ShaderProgram* ShaderProgram::currentProgram(NULL);

ShaderProgram::ShaderProgram() : programHandle(0) {
}

ShaderProgram::~ShaderProgram() {
	if(programHandle != 0) {
		glDeleteProgram(programHandle);
	}
}

bool ShaderProgram::makeProgram(const std::string &vp_filename, const std::string &fp_filename) {
	//LOAD AND COMPILE VERTEX SHADER
	std::cout << "* Loading new vertex shader from " << vp_filename << std::endl;;
	Shader vertex(GL_VERTEX_SHADER);
	vertex.load(vp_filename);
	if (!vertex.compile()) {
		vertex.printInfoLog();
		std::cout << "#ERROR Compile failed for vertex shader '" << vp_filename << "'." << std::endl;;
		return false;
	}
	else std::cout << " - Compiled " << vp_filename << " successfully." << std::endl;;

	//LOAD AND COMPILE FRAGMENT SHADER
	std::cout << "* Loading new fragment shader from " << fp_filename << std::endl;;
	Shader fragment(GL_FRAGMENT_SHADER);
	fragment.load(fp_filename);
	if (!fragment.compile()) {
		fragment.printInfoLog();
		std::cout << "#ERROR Compile failed for fragment shader '" << fp_filename << "'." << std::endl;
		return false;
	}
	else std::cout <<  " - Compiled " << fp_filename << " successfully." << std::endl;

	//CREATE THE PROGRAM
	std::cout << "* Creating new shaderProgram with " << vp_filename << " and " << fp_filename << std::endl;
	programHandle = glCreateProgram();

	//ATTACH AND LINK
	vertex.attach(programHandle);
	fragment.attach(programHandle);
	glLinkProgram(programHandle);

	//CHECK FOR LINK SUCCESS
	GLint success;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		printInfoLog();
		std::cout << "#ERROR Linking program failed!" << std::endl;
		return false;
	}
	else std::cout <<  " - Linked " << vp_filename << " and " << fp_filename << " successfully. PROGRAMID: " << programHandle << std::endl;

	//RETRIEVE ATTRIBUTE DATA
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

	//RETRIEVE UNIFORM INFO
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

	//PRINT ATTRIBUTE INFO
	std::cout << "--------------" << std::endl;
	std::cout << "Printing attribute info:" << std::endl;
	for(std::map<std::string,GLint>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
		std::cout << it->first << " at location " << it->second << std::endl;
	}

	//PRINT UNIFORM INFO
	std::cout << "Printing uniform info:" << std::endl;
	for(std::map<std::string,Uniform*>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
		std::cout << it->first << ":" << std::endl;
		it->second->log();
	}
	std::cout << "--------------" << std::endl;
	return true;
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

void ShaderProgram::useProgram(std::string name) {
	ShaderProgram* newSP = programs.at(name);
	if(currentProgram == NULL || newSP->programHandle != currentProgram->programHandle) {
		currentProgram = newSP;
		glUseProgram(newSP->programHandle);
	}
}

void ShaderProgram::add(std::string name, ShaderProgram *program) {
	ShaderProgram::programs.insert(std::pair<std::string,ShaderProgram*>(name,program));
}

void ShaderProgram::ready() {
	for(std::map<std::string,Uniform*>::iterator it = currentProgram->uniforms.begin(); it != currentProgram->uniforms.end(); ++it) {
		it->second->ready();
	}
}

Uniform* ShaderProgram::uniform(std::string name) {
	return currentProgram->uniforms.at(name);
}
