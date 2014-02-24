#include "ShaderBinding.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

GLuint ShaderBinding::currentVAO = 0;

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) {
	VBE_ASSERT(mesh->getVertexBuffer() != 0, "nullptr vertex buffer when about to make binding;");
	VBE_DLOG("* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh );
	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject));
	GL_ASSERT(glBindVertexArray(vertexArrayObject));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()));
	if(mesh->isIndexed())
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer()));
	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string, GLint>::const_iterator it = program->attributes.begin(); it != program->attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->attr.hasName(it->first)) {
				GL_ASSERT(glEnableVertexAttribArray(it->second));
				if(current->conv == Vertex::Element::ConvertToInt)
					GL_ASSERT(glVertexAttribIPointer(it->second,
										  current->size,
										  current->type,
										  format.vertexSize(),
										  (GLvoid*)long(format.offset(i))));
				else
					GL_ASSERT(glVertexAttribPointer(it->second,
										  current->size,
										  current->type, current->conv == Vertex::Element::ConvertToFloatNormalized ? GL_TRUE : GL_FALSE,
										  format.vertexSize(),
										  (GLvoid*)long(format.offset(i))));
			}
		}
	}
	GL_ASSERT(glBindVertexArray(currentVAO));
}

ShaderBinding::~ShaderBinding() {
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject));
}

void ShaderBinding::bindVAO() const {
	VBE_ASSERT(vertexArrayObject != 0, "nullptr VAO when about to bind");
	if(vertexArrayObject != currentVAO) {
		GL_ASSERT(glBindVertexArray(vertexArrayObject));
		currentVAO = vertexArrayObject;
	}
}
