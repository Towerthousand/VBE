#include <VBE/graphics/Mesh.hpp>
#include <VBE/graphics/Model.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/system/Log.hpp>

Model::Model() : mesh(nullptr), program(nullptr) {
}

Model::~Model() {
}

void Model::draw() const {
	draw(0, mesh->getVertexCount());
}

void Model::draw(unsigned int offset, unsigned int length) const {
	VBE_ASSERT(mesh != nullptr, "Trying to draw with nullptr mesh pointer");
	VBE_ASSERT(program != nullptr, "Trying to draw with nullptr program pointer");
	mesh->draw(program, offset, length);
}
