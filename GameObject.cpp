#include "GameObject.hpp"

GameObject::GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale) :
	isAlive(true), pos(pos), scale(scale),
	parent(parent) {
}

GameObject::~GameObject() {
}

void GameObject::update(float deltaTime) {
	(void) deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addObject(GameObject *object) {
	objects.push_back(object);
}
