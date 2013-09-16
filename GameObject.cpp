#include "GameObject.hpp"

std::map<std::string,GameObject*> GameObject::IDmap;

GameObject::GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale, std::string ID) :
	isAlive(true), pos(pos), scale(scale),
	parent(parent), id(ID) {
	if(!id.empty())
		if(!IDmap.insert(std::pair<std::string,GameObject*>(id,this)).second)
			id = "";
}

GameObject::~GameObject() {
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		delete *it;
	if(!id.empty())
		IDmap.erase(id);
}

void GameObject::update(float deltaTime) {
	(void) deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addObject(GameObject *object) {
	children.push_back(object);
}

GameObject* GameObject::getObjectByID(std::string ID) {
	return IDmap.at(ID);
}
