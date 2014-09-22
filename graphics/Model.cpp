#include "Model.hpp"
#include "Mesh.hpp"

Model::Model() : mesh(nullptr), program(nullptr) {
}

Model::~Model() {
}

void Model::draw() const {
	draw(0, mesh->getVertexCount());
}

void Model::draw(unsigned int firstVertex, unsigned int vertexCount) const {
	VBE_ASSERT(mesh != nullptr, "Trying to draw with nullptr mesh pointer");
	VBE_ASSERT(program != nullptr, "Trying to draw with nullptr program pointer");
	mesh->draw(program, firstVertex, vertexCount);
}
