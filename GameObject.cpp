#include "GameObject.hpp"

GameObject::GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale) :
	isAlive(true), pos(pos), scale(scale),
	parent(parent) {
}

GameObject::~GameObject() {
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		delete *it;
}

void GameObject::update(float deltaTime) {
	(void) deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addObject(GameObject *object) {
	children.push_back(object);
}
