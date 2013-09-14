#include "TriangleObject.hpp"
#include "SceneMain.hpp"
#include "../Game.hpp"

TriangleObject::TriangleObject(Scene* parentScene,  const vec3f &pos, const vec3f &scale) : GameObject(parentScene,pos,scale) {
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
	m = glm::rotate(m,GLOBALCLOCK.getElapsedTime().asSeconds()*90,vec3f(0,1,0));
	m = glm::scale(m,scale);
	tri.modelMatrix = m;
}

void TriangleObject::draw() const {
	mat4f transform = parentScene->getState().projection*parentScene->getState().view*tri.modelMatrix;
	TextureManager::get("cubetex")->bind();
	tri.program->uniform("sampler")->set(2);
	tri.program->uniform("modelViewProjectionMatrix")->set(transform);
	tri.draw();
}
