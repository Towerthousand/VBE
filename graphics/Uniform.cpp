#include "Uniform.hpp"
#include "ShaderProgram.hpp"

Uniform::Uniform(unsigned int count, GLenum type, GLint location) :
	dirty(false), count(count), type(type), location(location) {
	unsigned int size = 0;
	switch(type) {
		case GL_FLOAT:
			size = sizeof(GLfloat);
			break;
		case GL_FLOAT_VEC3:
			size = sizeof(GLfloat)*3;
			break;
		case GL_FLOAT_MAT4:
			size = sizeof(GLfloat)*16;
			break;
		default:
			break;
	}
	size *= count;
	lastValue = std::vector<char>(size,0);
}

Uniform::~Uniform() {
}

void Uniform::set(float val) {assert(type == GL_FLOAT);setBytes((char*)&val);}
void Uniform::set(std::vector<float> val) {assert(type == GL_FLOAT);assert(val.size() == count);setBytes((char*)&val[0]);}

void Uniform::set(vec3f val) {assert(type == GL_FLOAT_VEC3);setBytes((char*)&val[0]);}
void Uniform::set(std::vector<vec3f> val) {assert(type == GL_FLOAT_VEC3);assert(val.size() == count);setBytes((char*)&val[0][0]);}

void Uniform::set(mat4f val) {assert(type == GL_FLOAT_MAT4);setBytes((char*)&val[0][0]);}
void Uniform::set(std::vector<mat4f> val) {assert(type == GL_FLOAT_MAT4);assert(val.size() == count);setBytes((char*)&val[0][0][0]);}

void Uniform::ready() { //assumes program is binded already. Only to be called by ShaderProgram
	if(!dirty) return;
	dirty = false;
	switch(type) {
		case GL_FLOAT: glUniform1fv(location,count,(GLfloat*)&lastValue[0]); break;
		case GL_FLOAT_VEC3:	glUniform3fv(location,count,(GLfloat*)&lastValue[0]); break;
		case GL_FLOAT_MAT4:	glUniformMatrix4fv(location,count,GL_FALSE,(GLfloat*)&lastValue[0]); break;
		default: break;
	}
}

void Uniform::setBytes(char* val) {
	if(!compare(val)) {
		for(unsigned int i = 0; i < lastValue.size(); ++i)
			lastValue[i] = val[i];
		dirty = true;
	}
}

bool Uniform::compare(char *val) const {
	for(unsigned int i = 0; i < lastValue.size(); ++i)
		if(lastValue[i] != val[i])
			return false;
	return true;
}

void Uniform::log() {
	std::cout << "Array of "		 << count
			  << " at location "	 << location
			  << ", with a size of " << lastValue.size()/count
			  <<" bytes per item and of type " ;
	switch(type) {
		case GL_FLOAT: std::cout << "GL_FLOAT"; break;
		case GL_FLOAT_VEC3: std::cout << "GL_FLOAT_VEC3"; break;
		case GL_FLOAT_MAT4: std::cout << "GL_FLOAT_MAT4"; break;
		default: break;
	}
	std::cout << std::endl;
}
