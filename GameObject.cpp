#include "GameObject.hpp"
#include "Game.hpp"

GameObject::GameObject() : id(Game::i()->objectCount++), isAlive(true), parent(NULL),
	transform(1.0f), fullTransform(1.0), game(Game::i()), drawPriority(0),
	updatePriority(0), name("") {
	game->objectCount++;
	game->attachObject(this);
	game->idMap.insert(std::pair<int,GameObject*>(id,this));
}

GameObject::~GameObject() {
	--game->objectCount;
	game->deattachObject(this);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		delete *it;
	if(!name.empty())
		game->nameMap.erase(name);
	game->idMap.erase(id);
}

void GameObject::update(float deltaTime) {
	(void) deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addObject(GameObject *object) {
	VBE_ASSERT(object->parent == NULL, "Trying to add a node that already has a parent. Remove it from it's parent first.");
	object->parent = this;
	children.push_back(object);
	onObjectAdd(object);
}

void GameObject::removeFromParent() {
	VBE_ASSERT(parent != NULL, "Trying to remove node from null parent. Add it to a parent node first.");
	parent->children.remove(this);
	parent = NULL;
}

void GameObject::setName(std::string newName) {
	if(name == newName) return;
	if(game->nameMap.insert(std::pair<std::string,GameObject*>(newName,this)).second) {
		if(!name.empty()) game->nameMap.erase(name);
		name = newName;
	}
	else {VBE_LOG("#WARNING Can't set name for node " << this << ". This name is already in use." );}
}

void GameObject::setDrawPriority(int newPriority) {
	if(drawPriority == newPriority) return;
	game->drawTasks.erase(this);
	drawPriority = newPriority;
	game->drawTasks.insert(this);
}

void GameObject::setUpdatePriority(int newPriority) {
	if(updatePriority == newPriority) return;
	game->Game::updateTasks.erase(this);
	updatePriority = newPriority;
	game->Game::updateTasks.insert(this);
}

std::string GameObject::getName() {
	return name;
}

int GameObject::getDrawPriority() {
	return drawPriority;
}

int GameObject::getUpdatePriority() {
	return updatePriority;
}

GameObject* GameObject::getObjectByName(std::string name) {
	return Game::i()->nameMap.at(name);
}

GameObject* GameObject::getObjectByID(int id) {
	return Game::i()->idMap.at(id);
}

void GameObject::onObjectAdd(GameObject* object) {
	(void) object;
}

void GameObject::calcFullTransform(mat4f parentFullTransform) {
	fullTransform = parentFullTransform * transform;
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->calcFullTransform(fullTransform);
}

bool GameObject::checkTree(GameObject* root, int& nulls) {
	GameObject* parent = root->parent;
	if(parent != NULL) {
		int count = 0;
		for(std::list<GameObject*>::iterator it = parent->children.begin(); it != parent->children.end(); ++it)
			if(*it == root) ++count;
		if(count != 1) return false;
	}
	else ++nulls;
	if(nulls > 1) return false;
	for(std::list<GameObject*>::iterator it = root->children.begin(); it != root->children.end(); ++it)
		if(!checkTree(*it,nulls)) return false;
	return true;
}
