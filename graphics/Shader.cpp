#include "Shader.hpp"

Shader::Shader(GLenum type) {
	shaderHandle = glCreateShader(type);
}

Shader::~Shader() {
	glDeleteShader(shaderHandle);
}

Shader* Shader::makeShader(const std::string& data, GLenum shaderType, bool raw) {
	std::string out = (!raw? data: "string");
	switch(shaderType) {
		case GL_FRAGMENT_SHADER:
			VBE_DLOG("* Loading new fragment shader from " << out );
			break;
		case GL_GEOMETRY_SHADER:
			VBE_DLOG("* Loading new geometry shader from " << out );
			break;
		case GL_VERTEX_SHADER:
			VBE_DLOG("* Loading new vertex shader from " << out );
			break;
		default:
			break;
	}
	out.clear();
	Shader* s = new Shader(shaderType);
	if(raw) s->loadRaw(data);
	else s->load(data);
	s->compile();
	VBE_DLOG( " - Compiled " << data << " successfully." );
	return s;
}

void Shader::load(const std::string &filename) {
	std::ifstream is;
	is.open(filename, std::ios::in);
	VBE_ASSERT(!is.fail(),"Failed to get the contents from " << filename );

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
	glShaderSource(shaderHandle, 1, &source, NULL);
}

void Shader::loadRaw(const std::string &content) {
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
	VBE_ASSERT(program != 0, "Trying to attach shader with id " << shaderHandle << " to null program");
	glAttachShader(program, shaderHandle);
}

void Shader::printInfoLog() const {
	VBE_ASSERT(shaderHandle != 0, "Trying to query null shader");
	int length = 0;
	glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		char infoLog[length];
		glGetShaderInfoLog(shaderHandle, length, NULL, infoLog);
		VBE_LOG(infoLog );
	}
}
