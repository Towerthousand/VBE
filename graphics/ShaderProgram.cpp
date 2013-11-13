#include "ShaderProgram.hpp"
#include "Uniform.hpp"
#include "Shader.hpp"

GLuint ShaderProgram::current(0);

ShaderProgram::ShaderProgram() : programHandle(0) {
}

ShaderProgram::~ShaderProgram() {
	if(programHandle != 0) {
		glDeleteProgram(programHandle);
	}
	for(std::map<std::string,Uniform*>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
		delete it->second;
	}
}

void ShaderProgram::makeProgram(const std::string &vp_filename, const std::string &fp_filename, bool raw) {
	VBE_ASSERT(programHandle == 0, "Trying to remake an already made program!");
	Shader* vertex = Shader::makeShader(vp_filename, GL_VERTEX_SHADER, raw);
	Shader* fragment = Shader::makeShader(fp_filename, GL_FRAGMENT_SHADER, raw);

	if(!raw) {
		VBE_DLOG("* Creating new shaderProgram with " << vp_filename << " and " << fp_filename );
	}
	else {
		VBE_DLOG("* Creating new shaderProgram with two raw strings");
	}

	programHandle = glCreateProgram();

	vertex->attach(programHandle);
	fragment->attach(programHandle);
	link();
	retriveProgramInfo();
	delete vertex;
	delete fragment;
}

void ShaderProgram::makeProgram(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename, bool raw) {
	Shader* vertex = Shader::makeShader(vp_filename, GL_VERTEX_SHADER, raw);
	Shader* geometry = Shader::makeShader(gp_filename, GL_GEOMETRY_SHADER, raw);
	Shader* fragment = Shader::makeShader(fp_filename, GL_FRAGMENT_SHADER, raw);
	VBE_DLOG(vp_filename);
	if(!raw) {
		VBE_DLOG("* Creating new shaderProgram with " << vp_filename << ", " << gp_filename << " and " << fp_filename );
	}
	else {
		VBE_DLOG("* Creating new shaderProgram with three raw strings");
	}

	programHandle = glCreateProgram();

	vertex->attach(programHandle);
	geometry->attach(programHandle);
	fragment->attach(programHandle);
	link();
	retriveProgramInfo();
	delete vertex;
	delete geometry;
	delete fragment;
}

void ShaderProgram::printInfoLog() {
	VBE_ASSERT(programHandle != 0, "Trying to query nullptr program");
	int length = 0;
	glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetProgramInfoLog(programHandle, length, nullptr, infoLog);
		VBE_LOG(infoLog );
	}
}

void ShaderProgram::use() const {
	VBE_ASSERT(programHandle != 0, "Trying to use nullptr program");
	if(current != programHandle) {
		current = programHandle;
		glUseProgram(programHandle);
	}
	for(std::map<std::string,Uniform*>::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
		it->second->ready();
}

Uniform* ShaderProgram::uniform(const std::string &name) const {
	VBE_ASSERT(uniforms.find(name) != uniforms.end(), "Trying to retrieve unexisting uniform " << name);
	VBE_ASSERT(programHandle != 0, "Trying to retrieve uniform from nullptr program");
	return uniforms.at(name);
}

void ShaderProgram::link() {
	glLinkProgram(programHandle);
	//CHECK FOR LINK SUCCESS
	GLint success;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		printInfoLog();
		VBE_ASSERT(false, "#ERROR Linking program failed!" );
	}
	VBE_DLOG( " - Linked program successfully. PROGRAMID: " << programHandle );
}

void ShaderProgram::retriveProgramInfo() {
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
				glGetActiveAttrib(programHandle, i, length, nullptr, &attribSize, &attribType, attribName);
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
				glGetActiveUniform(programHandle, i, length, nullptr, &uniformSize, &uniformType, uniformName);
				uniformName[length] = '\0';  // nullptr terminate
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
	VBE_DLOG("--------------" );
	VBE_DLOG("Printing attribute info:" );
	for(std::map<std::string,GLint>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
		VBE_DLOG(it->first << " at location " << it->second );
	}

	//PRINT UNIFORM INFO
	VBE_DLOG("Printing uniform info:" );
	for(std::map<std::string,Uniform*>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
		VBE_DLOG(it->first << ":" );
		it->second->log();
	}
	VBE_DLOG("--------------" );
}
