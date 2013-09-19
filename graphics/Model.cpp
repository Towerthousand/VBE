#include "Model.hpp"
#include "Mesh.hpp"
#include "../Game.hpp"

Model::Model() : modelMatrix(mat4f(1.0)), mesh(NULL) {
}

Model::~Model() {
}

void Model::draw() const {
	VBE_ASSERT(mesh != NULL, "Trying to draw with NULL mesh pointer")
	mesh->draw(program);
}
