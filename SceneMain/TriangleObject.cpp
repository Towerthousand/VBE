#include "TriangleObject.hpp"
#include "../Game.hpp"

TriangleObject::TriangleObject(GameObject* parent,  const vec3f &pos, const vec3f &scale) : GameObject(parent,pos,scale) {
	tri.mesh = MeshManager::get("cube");
	tri.program = ShaderManager::get("sample");
}

TriangleObject::~TriangleObject() {
}

void TriangleObject::update(float deltaTime) {
	(void) deltaTime;
	updateMatrix();
}

void TriangleObject::updateMatrix() {
	mat4f m(1.0);
	m = glm::translate(m,pos);
	//m = glm::rotate(m,GLOBALCLOCK.getElapsedTime().asSeconds()*90,vec3f(0,1,0));
	m = glm::scale(m,scale);
	tri.modelMatrix = m;
}

void TriangleObject::draw() const {
	RenderState::model *= tri.modelMatrix;
	mat4f transform = RenderState::projection*RenderState::view*RenderState::model;
	tri.program->uniform("sampler")->set(TextureManager::get("cubetex"));
	tri.program->uniform("modelViewProjectionMatrix")->set(transform);
	tri.draw();
}
