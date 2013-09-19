#include "GameObject.hpp"
#include "RenderState.hpp"
#include "Game.hpp"

std::map<std::string,GameObject*> GameObject::nameMap;
std::map<int,GameObject*> GameObject::idMap;
int GameObject::idCounter = 1;
int GameObject::objectCount = 0;

GameObject::GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale) :
	pos(pos), scale(scale), id(idCounter++), isAlive(true),
	parent(parent), drawPriority(0), name("") {
	++objectCount;
	idMap.insert(std::pair<int,GameObject*>(id,this));
}

GameObject::~GameObject() {
	--objectCount;
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
	object->setDrawPriority(drawPriority);
}

void GameObject::setName(std::string newName) {
	if(nameMap.insert(std::pair<std::string,GameObject*>(newName,this)).second) {
		if(!name.empty()) nameMap.erase(name);
		name = newName;
	}
}

void GameObject::setDrawPriority(int newPriority) {
	VBE_ASSERT(newPriority >= drawPriority || parent == NULL || parent->getDrawPriority() <= newPriority,
			   "Invalid priority for gameobject with id " << this->id)
	drawPriority = newPriority;
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->setDrawPriority(newPriority);
}

int GameObject::getDrawPriority() {
	return drawPriority;
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

int GameObject::getObjectCount() {
	return objectCount;
}

void GameObject::doUpdate(float deltaTime) {
	update(deltaTime);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end();) {
		(*it)->doUpdate(deltaTime);
		if (!(*it)->isAlive) {
			delete *it;
			it = children.erase(it);;
		}
		else
			++it;
	}
}

void GameObject::doDraw() {
	VBE_ASSERT(drawPriority >= Game::drawLayer, "Draw priority is messed up. Internal error (?). Object id: " << this->id)
	if(drawPriority == Game::drawLayer) {
		RenderState::push();
		this->draw();
		for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
			(*it)->doDraw();
		RenderState::pop();
	}
	else {
		RenderState::RenderInstance currState = RenderState::getCurrent();
		Game::addDrawTask(currState,this);
	}
}
