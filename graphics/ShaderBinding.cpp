#include "ShaderBinding.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) {
	std::cout << "New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh << std::endl;
	glGenVertexArrays(1, &m_vertexArrayObject);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to create VAO for mesh")
	glBindVertexArray(m_vertexArrayObject);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to bind VAO with id " << m_vertexArrayObject)
	glBindBuffer(GL_ARRAY_BUFFER,mesh->getVertexBuffer());
	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string,GLint>::const_iterator it = program->m_attributes.begin(); it != program->m_attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->m_attr.hasName(it->first)) {
				glEnableVertexAttribArray(it->second);
				glVertexAttribPointer(it->second,
									  current->m_size,
									  current->m_type, GL_FALSE,
									  format.vertexSize(),
									  (GLvoid*)long(format.offset(i)));
			}
		}
	}
	glBindVertexArray(0);
}

ShaderBinding::~ShaderBinding() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void ShaderBinding::bindVAO() const {
	glBindVertexArray(m_vertexArrayObject);
}

void ShaderBinding::unbindVAO() const {
	glBindVertexArray(0);
}
