#include "GameObject.hpp"

std::map<std::string,GameObject*> GameObject::nameMap;
std::map<int,GameObject*> GameObject::idMap;
int GameObject::idCounter = 1;

GameObject::GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale) :
	pos(pos), scale(scale), id(idCounter++), isAlive(true),
	parent(parent), name("") {
	idMap.insert(std::pair<int,GameObject*>(id,this));
}

GameObject::~GameObject() {
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		delete *it;
	if(!name.empty())
		nameMap.erase(name);
	idMap.erase(id);
}

void GameObject::update(float deltaTime) {
	(void) deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addObject(GameObject *object) {
	children.push_back(object);
}

void GameObject::setName(std::string newName) {
	if(nameMap.insert(std::pair<std::string,GameObject*>(newName,this)).second) {
		if(!name.empty()) nameMap.erase(name);
		name = newName;
	}
}

std::string GameObject::getName() {
	return name;
}

GameObject* GameObject::getObjectByName(std::string name) {
	return nameMap.at(name);
}

GameObject* GameObject::getObjectByID(int id) {
	return idMap.at(id);
}
