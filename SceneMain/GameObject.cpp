#include "GameObject.hpp"
#include "SceneMain.hpp"

GameObject::GameObject(SceneMain* scene, const vec3f &pos, const vec3f &scale) :
	isAlive(true), pos(pos), scale(scale),
	parentScene(scene),
	modelMatrix(mat4f(1.0)) {
}

GameObject::~GameObject() {
}

void GameObject::update(float deltaTime) {
}

void GameObject::updateMatrix() {
}

void GameObject::draw() const {
}
