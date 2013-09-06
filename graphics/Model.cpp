#include "Model.hpp"
#include "Mesh.hpp"
#include "../Game.hpp"

Model::Model() : modelMatrix(mat4f(1.0)), mesh(NULL) {
}

Model::~Model() {
}

void Model::draw() const {
	mesh->draw(program);
}
