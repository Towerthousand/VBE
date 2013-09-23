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

bool ShaderProgram::makeProgram(const std::string &vp_filename, const std::string &fp_filename) {
	//LOAD AND COMPILE VERTEX SHADER
	VBE_DLOG("* Loading new vertex shader from " << vp_filename );
	Shader vertex(GL_VERTEX_SHADER);
	if(!vertex.load(vp_filename))
		return false;
	if (!vertex.compile()) {
		vertex.printInfoLog();
		VBE_LOG("#ERROR Compile failed for vertex shader '" << vp_filename << "'." );
		return false;
	}
	else {VBE_DLOG(" - Compiled " << vp_filename << " successfully." );}

	//LOAD AND COMPILE FRAGMENT SHADER
	VBE_DLOG("* Loading new fragment shader from " << fp_filename );
	Shader fragment(GL_FRAGMENT_SHADER);
	if(!fragment.load(fp_filename))
		return false;
	if (!fragment.compile()) {
		fragment.printInfoLog();
		VBE_LOG("#ERROR Compile failed for fragment shader '" << fp_filename << "'." );
		return false;
	}
	else {VBE_DLOG( " - Compiled " << fp_filename << " successfully." );}

	//CREATE THE PROGRAM
	VBE_DLOG("* Creating new shaderProgram with " << vp_filename << " and " << fp_filename );
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
		VBE_LOG("#ERROR Linking program failed!" );
		return false;
	}
	else {VBE_DLOG( " - Linked " << vp_filename << " and " << fp_filename << " successfully. PROGRAMID: " << programHandle );}

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
	return true;
}

void ShaderProgram::printInfoLog() {
	VBE_ASSERT(programHandle != 0, "Trying to query null program");
	int length = 0;
	glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetProgramInfoLog(programHandle, length, NULL, infoLog);
		VBE_LOG(infoLog );
	}
}

void ShaderProgram::use() const {
	VBE_ASSERT(programHandle != 0, "Trying to use null program");
	if(current != programHandle) {
		current = programHandle;
		glUseProgram(programHandle);
	}
	for(std::map<std::string,Uniform*>::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
		it->second->ready();
	}
}

Uniform* ShaderProgram::uniform(const std::string &name) const {
	VBE_ASSERT(uniforms.find(name) != uniforms.end(), "Trying to retrieve unexisting uniform " << name);
	VBE_ASSERT(programHandle != 0, "Trying to retrieve uniform from null program");
	return uniforms.at(name);
}
