#include "ShaderBinding.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) {
	glGenVertexArrays(1, &vertexArrayObject);
	if (glGetError()){
		std::cout << "Failed to create VAO for mesh" << std::endl;
	}

    //program->use();

	glBindVertexArray(vertexArrayObject);
	if (glGetError()) {
		std::cout << "Failed to bind VAO with id " << vertexArrayObject << std::endl;
		glDeleteVertexArrays(1, &vertexArrayObject);
        return;
	}

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
	glDeleteBuffers(1, &vertexArrayObject);
}

void ShaderBinding::bindVAO() const {
	glBindVertexArray(vertexArrayObject);
}

void ShaderBinding::unbindVAO() const {
	glBindVertexArray(0);
}
