#include "ShaderBinding.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

GLuint ShaderBinding::currentVAO = 0;

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) {
	VBE_ASSERT(mesh->getVertexBuffer() != 0, "nullptr vertex buffer when about to make binding;");
	VBE_DLOG("* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh );
	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject), "Failed to create VAO for mesh");
	GL_ASSERT(glBindVertexArray(vertexArrayObject), "Failed to bind VAO with id " << vertexArrayObject);
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()), "Failed to bind VBO for mesh");
	if(mesh->isIndexed())
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer()), "Failed to bind IBO for mesh");
	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string, GLint>::const_iterator it = program->attributes.begin(); it != program->attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->attr.hasName(it->first)) {
				GL_ASSERT(glEnableVertexAttribArray(it->second), "Failed to enable vertex attribute");
				if(current->conv == Vertex::Element::ConvertToInt)
					GL_ASSERT(glVertexAttribIPointer(it->second,
										  current->size,
										  current->type,
										  format.vertexSize(),
										  (GLvoid*)long(format.offset(i))),
							  "Failed to set vertex attribute integer pointer");
				else
					GL_ASSERT(glVertexAttribPointer(it->second,
										  current->size,
										  current->type, current->conv == Vertex::Element::ConvertToFloatNormalized ? GL_TRUE : GL_FALSE,
										  format.vertexSize(),
										  (GLvoid*)long(format.offset(i))),
							  "Failed to set vertex attribute pointer");
			}
		}
	}
	GL_ASSERT(glBindVertexArray(currentVAO), "Failed to bind VAO");
}

ShaderBinding::~ShaderBinding() {
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject), "Failed to delete VAO");
}

void ShaderBinding::bindVAO() const {
	VBE_ASSERT(vertexArrayObject != 0, "nullptr VAO when about to bind");
	if(vertexArrayObject != currentVAO) {
		GL_ASSERT(glBindVertexArray(vertexArrayObject), "Failed to bind VAO");
		currentVAO = vertexArrayObject;
	}
}
