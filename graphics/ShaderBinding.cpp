#include "ShaderBinding.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) {
	std::cout << "* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh << std::endl;
	glGenVertexArrays(1, &vertexArrayObject);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to create VAO for mesh")
	glBindVertexArray(vertexArrayObject);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to bind VAO with id " << vertexArrayObject)
	glBindBuffer(GL_ARRAY_BUFFER,mesh->getVertexBuffer());
	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string,GLint>::const_iterator it = program->attributes.begin(); it != program->attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->attr.hasName(it->first)) {
				glEnableVertexAttribArray(it->second);
				glVertexAttribPointer(it->second,
									  current->size,
									  current->type, GL_FALSE,
									  format.vertexSize(),
									  (GLvoid*)long(format.offset(i)));
			}
		}
	}
	glBindVertexArray(0);
}

ShaderBinding::~ShaderBinding() {
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void ShaderBinding::bindVAO() const {
	glBindVertexArray(vertexArrayObject);
}

void ShaderBinding::unbindVAO() const {
	glBindVertexArray(0);
}
