#include "Model.hpp"
#include "Mesh.hpp"
#include "../Game.hpp"

Model::Model() : m_modelMatrix(mat4f(1.0)), m_mesh(NULL) {
}

Model::~Model() {
}

void Model::draw() const {
	VBE_ASSERT(m_mesh != NULL, "Trying to draw with NULL mesh pointer")
	m_mesh->draw(m_program);
}
