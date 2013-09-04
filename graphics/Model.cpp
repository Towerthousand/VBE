#include "Model.hpp"
#include "Mesh.hpp"
#include "../Game.hpp"

Model::Model() : modelMatrix(mat4f(1.0)), mesh(NULL) {
}

Model::~Model() {
}

void Model::draw() const {
	program->use();
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
	int offset = 0;
	for(unsigned int i = 0; i != mesh->getVertexFormat().elementCount(); ++i) {
		const Vertex::Element& current = mesh->getVertexFormat().element(i);
		glEnableVertexAttribArray(current.attr.ID());
		glVertexAttribPointer(current.attr.ID(),
							  current.size,
							  current.type, GL_FALSE,
							  mesh->getVertexSize(),
							  (GLvoid*)long(offset));
		offset += current.size*
				  sizeof(mesh->getVertexFormat().element(i).type);
	}

	glDrawArrays(mesh->getPrimitiveType(), 0, mesh->getVertexCount());

	for(unsigned int i = 0; i != mesh->getVertexFormat().elementCount(); ++i) {
		glDisableVertexAttribArray(mesh->getVertexFormat().element(i).attr.ID());
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
