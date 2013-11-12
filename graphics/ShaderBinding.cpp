#include "ShaderBinding.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

GLuint ShaderBinding::currentVAO = 0;

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) {
	VBE_ASSERT(mesh->getVertexBuffer() != 0, "nullptr vertex buffer when about to make binding;");
	VBE_DLOG("* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh );
	glGenVertexArrays(1, &vertexArrayObject);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to create VAO for mesh");
	glBindVertexArray(vertexArrayObject);
	VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to bind VAO with id " << vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER,mesh->getVertexBuffer());
	if(mesh->isIndexed())
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh->getIndexBuffer());
	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string,GLint>::const_iterator it = program->attributes.begin(); it != program->attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->attr.hasName(it->first)) {
				glEnableVertexAttribArray(it->second);
				if(current->type == Vertex::Element::Float ||
				   current->type == Vertex::Element::Double ||
				   current->type == Vertex::Element::Fixed)
					glVertexAttribPointer(it->second,
										  current->size,
										  current->type, GL_FALSE,
										  format.vertexSize(),
										  (GLvoid*)long(format.offset(i)));
				else
					glVertexAttribIPointer(it->second,
										  current->size,
										  current->type,
										  format.vertexSize(),
										  (GLvoid*)long(format.offset(i)));
			}
		}
	}
	glBindVertexArray(currentVAO);
}

ShaderBinding::~ShaderBinding() {
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void ShaderBinding::bindVAO() const {
	VBE_ASSERT(vertexArrayObject != 0, "nullptr VAO when about to bind");
	if(vertexArrayObject != currentVAO) {
		glBindVertexArray(vertexArrayObject);
		currentVAO = vertexArrayObject;
	}
}
