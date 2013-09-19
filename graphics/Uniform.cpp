#include "Uniform.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

Uniform::Uniform(unsigned int count, GLenum type, GLint location) :
	m_dirty(true), m_count(count), m_type(type), m_location(location) {
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
		case GL_INT:
			size = sizeof(GLint);
			break;
		case GL_SAMPLER_2D:
			size = sizeof(GLint);
			break;
		default:
			VBE_ASSERT(false, "Unreconised uniform type " << type) break;
	}
	size *= count;
	m_lastValue = std::vector<char>(size,0);
}

Uniform::~Uniform() {
}

void Uniform::set(int val) {
	VBE_ASSERT(m_type == GL_INT || m_type == GL_SAMPLER_2D, "Wrong uniform type. Location " << this->m_location)
	setBytes((char*)&val);
}
void Uniform::set(const std::vector<int> &val) {
	VBE_ASSERT(m_type == GL_INT || m_type == GL_SAMPLER_2D, "Wrong uniform type. Location " << this->m_location)
	VBE_ASSERT(val.size() == m_count, "Wrong vector size. Location " << this->m_location)
	setBytes((char*)&val[0]);
}

void Uniform::set(float val) {
	VBE_ASSERT(m_type == GL_FLOAT, "Wrong uniform type. Location " << this->m_location)
	setBytes((char*)&val);
}
void Uniform::set(const std::vector<float> &val) {
	VBE_ASSERT(m_type == GL_FLOAT, "Wrong uniform type. Location " << this->m_location)
	VBE_ASSERT(val.size() == m_count, "Wrong vector size. Location " << this->m_location)
	setBytes((char*)&val[0]);}

void Uniform::set(const vec3f &val) {
	VBE_ASSERT(m_type == GL_FLOAT_VEC3, "Wrong uniform type. Location " << this->m_location)
	setBytes((char*)&val[0]);
}
void Uniform::set(const std::vector<vec3f> &val) {
	VBE_ASSERT(m_type == GL_FLOAT_VEC3, "Wrong uniform type. Location " << this->m_location)
	VBE_ASSERT(val.size() == m_count, "Wrong vector size. Location " << this->m_location)
	setBytes((char*)&val[0][0]);
}

void Uniform::set(const mat4f &val) {
	VBE_ASSERT(m_type == GL_FLOAT_MAT4, "Wrong uniform type. Location " << this->m_location)
	setBytes((char*)&val[0][0]);
}
void Uniform::set(const std::vector<mat4f> &val) {
	VBE_ASSERT(m_type == GL_FLOAT_MAT4, "Wrong uniform type. Location " << this->m_location)
	VBE_ASSERT(val.size() == m_count, "Wrong vector size. Location " << this->m_location)
	setBytes((char*)&val[0][0][0]);
}

void Uniform::set(const Texture* val) {
	VBE_ASSERT(m_type == GL_SAMPLER_2D, "Wrong uniform type. Location " << this->m_location)
	val->bind();
	unsigned int slot = val->getSlot();
	setBytes((char*)&slot);}

void Uniform::ready() { //assumes program is binded already. Only to be called by ShaderProgram
	if(!m_dirty) return;
	m_dirty = false;
	switch(m_type) {
		case GL_FLOAT:		glUniform1fv(m_location,m_count,(GLfloat*)&m_lastValue[0]); break;
		case GL_FLOAT_VEC3:	glUniform3fv(m_location,m_count,(GLfloat*)&m_lastValue[0]); break;
		case GL_FLOAT_MAT4:	glUniformMatrix4fv(m_location,m_count,GL_FALSE,(GLfloat*)&m_lastValue[0]); break;
		case GL_INT:		glUniform1iv(m_location,m_count,(GLint*)&m_lastValue[0]); break;
		case GL_SAMPLER_2D:	glUniform1iv(m_location,m_count,(GLint*)&m_lastValue[0]); break;
		default:
			VBE_ASSERT(false, "Unreconised uniform type " << m_type)
			break;
	}
}

void Uniform::setBytes(const char *val) {
	if(!compare(val)) {
		for(unsigned int i = 0; i < m_lastValue.size(); ++i)
			m_lastValue[i] = val[i];
		m_dirty = true;
	}
}

bool Uniform::compare(const char *val) const {
	for(unsigned int i = 0; i < m_lastValue.size(); ++i)
		if(m_lastValue[i] != val[i])
			return false;
	return true;
}

void Uniform::log() {
	std::cout << "Array of "		 << m_count
			  << " at location "	 << m_location
			  << ", with a size of " << m_lastValue.size()/m_count
			  <<" bytes per item and of type " ;
	switch(m_type) {
		case GL_FLOAT: std::cout << "GL_FLOAT"; break;
		case GL_FLOAT_VEC3: std::cout << "GL_FLOAT_VEC3"; break;
		case GL_FLOAT_MAT4: std::cout << "GL_FLOAT_MAT4"; break;
		case GL_INT: std::cout << "GL_INT"; break;
		case GL_SAMPLER_2D: std::cout << "GL_SAMPLER_2D"; break;
		default: std::cout << "UNKNOWN_TYPE"; break;
	}
	std::cout << std::endl;
}
