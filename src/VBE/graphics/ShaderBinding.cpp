#include "ShaderBinding.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

#ifdef SHADERBINDING_USE_VAO
GLuint ShaderBinding::currentVAO = 0;
#endif

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) :
		program(program), mesh(mesh) {
	VBE_DLOG("* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh );
#ifdef SHADERBINDING_USE_VAO
	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject));
	GL_ASSERT(glBindVertexArray(vertexArrayObject));
	applyAttributes();
	GL_ASSERT(glBindVertexArray(currentVAO));
#endif
}

ShaderBinding::~ShaderBinding() {
#ifdef SHADERBINDING_USE_VAO
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject));
#endif
}

void ShaderBinding::enable() const {
#ifdef SHADERBINDING_USE_VAO
	VBE_ASSERT(vertexArrayObject != 0, "nullptr VAO when about to bind");
	if(vertexArrayObject != currentVAO) {
		GL_ASSERT(glBindVertexArray(vertexArrayObject));
		currentVAO = vertexArrayObject;
	}
#else
	applyAttributes();
#endif
}

void ShaderBinding::applyAttributes() const {
	VBE_ASSERT(mesh->getVertexBuffer() != 0, "mesh vertex buffer is null");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()));
	if(mesh->isIndexed()) {
		VBE_ASSERT(mesh->getIndexBuffer() != 0, "mesh index buffer is null");
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer()));
	}

	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string, GLint>::const_iterator it = program->attributes.begin(); it != program->attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->attr.hasName(it->first)) {
				GL_ASSERT(glEnableVertexAttribArray(it->second));
#ifndef VBE_GLES2
                if(current->conv == Vertex::Element::ConvertToInt)
                    GL_ASSERT(glVertexAttribIPointer(it->second,
                                                     current->size,
                                                     current->type,
                                                     format.vertexSize(),
                                                     (GLvoid*)long(format.offset(i))));
                else
#endif
					GL_ASSERT(glVertexAttribPointer(it->second,
													current->size,
													current->type, current->conv == Vertex::Element::ConvertToFloatNormalized ? GL_TRUE : GL_FALSE,
													format.vertexSize(),
													(GLvoid*)long(format.offset(i))));
			}
		}
	}
}
