#include "Model.hpp"
#include "Mesh.hpp"
#include "../Game.hpp"

Model::Model() : modelMatrix(mat4f(1.0)), mesh(NULL), program(NULL) {
}

Model::~Model() {
}

void Model::draw() const {
	VBE_ASSERT(mesh != NULL, "Trying to draw with null mesh pointer");
	VBE_ASSERT(program != NULL, "Trying to draw with null program pointer");
	mesh->draw(program);
}
