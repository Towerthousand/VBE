#include "TexturedObject.hpp"
#include "../Game.hpp"
#include "RegularPolygonObject.hpp"

TexturedObject::TexturedObject(GameObject* parent,  const vec3f &pos, const vec3f &scale) : GameObject(parent,pos,scale) {
	tri.mesh = MeshManager::get("cube");
	tri.program = ShaderManager::get("sample");
}

TexturedObject::~TexturedObject() {
}

void TexturedObject::update(float deltaTime) {
	(void) deltaTime;
	updateMatrix();
}

void TexturedObject::updateMatrix() {
	mat4f m(1.0);
	m = glm::translate(m,pos);
	m = glm::scale(m,scale);
	transform = m;
}

void TexturedObject::draw() const {
	tri.program->uniform("sampler")->set(TextureManager::get("cubetex"));
	tri.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	tri.draw();
}
