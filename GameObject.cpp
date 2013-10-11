#include "GameObject.hpp"
#include "Game.hpp"

GameObject::GameObject() : id(Game::i()->idCounter++),
	transform(1.0f), fullTransform(1.0), parent(NULL), drawPriority(0),
	updatePriority(0), name(""), inGame(false), isAlive(true) {
	Game::i()->idMap.insert(std::pair<int,GameObject*>(id,this));
}

GameObject::~GameObject() {
	//erase traces from the object
	if(!name.empty())
		Game::i()->nameMap.erase(name);
	Game::i()->idMap.erase(id);
}

void GameObject::update(float deltaTime) {
	(void)deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addTo(GameObject *newParent) {
	//Called whenever we want to add an object to a parent object
	VBE_ASSERT(this != Game::i()->getRoot(), "Cannot perform this operation on root node");
	VBE_ASSERT(parent == NULL, "Trying to attach a node that is already attached.");
	parent = newParent;
	parent->children.push_back(this);
	parent->onObjectAdd(this);
	if(parent->inGame)
		addToGame();
}

void GameObject::removeAndDelete() {
	//This will remove the object from the tree and it will tell the game to stop tracking
	//these objects and delete them.
	removeFromParent();
	markForDelete();
}

void GameObject::setName(std::string newName) {
	if(name == newName) return;
	if(Game::i()->nameMap.insert(std::pair<std::string,GameObject*>(newName,this)).second) {
		if(!name.empty()) Game::i()->nameMap.erase(name);
		name = newName;
	}
	else {VBE_ASSERT(false,"Can't set name " << newName << " for node " << this << ". This name is already in use." );}
}

int GameObject::getDrawPriority() const {
	return drawPriority;
}

int GameObject::getUpdatePriority() const {
	return updatePriority;
}

void GameObject::setDrawPriority(int newPriority) {
	VBE_ASSERT(!inGame, "You can't change the priority of an object that is in the game.");
	if(drawPriority == newPriority) return;
	if(parent != NULL) {
		Game::i()->objectTasksToRemove.push(this);
		Game::i()->objectTasksToAdd.push(this);
	}
	drawPriority = newPriority;
}

void GameObject::setUpdatePriority(int newPriority) {
	VBE_ASSERT(!inGame, "You can't change the priority of an object that is in the game.");
	if(updatePriority == newPriority) return;
	if(parent != NULL) {
		Game::i()->objectTasksToRemove.push(this);
		Game::i()->objectTasksToAdd.push(this);
	}
	updatePriority = newPriority;
}

Game*GameObject::getGame() const {
	return Game::i();
}

std::string GameObject::getName() const {
	return name;
}

const std::list<GameObject*>& GameObject::getChildren() const {
	return children;
}

void GameObject::onObjectAdd(GameObject* object) {
	(void)object;
}

void GameObject::removeFromParent() {
	VBE_ASSERT(parent != NULL, "Trying to detach a not attached node.");
	parent->children.remove(this);
	if(inGame)
		removeFromGame();
	parent = NULL;
}

void GameObject::calcFullTransform(mat4f parentFullTransform) {
	fullTransform = parentFullTransform * transform;
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->calcFullTransform(fullTransform);
}

void GameObject::markForDelete() {
	isAlive = false;
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->markForDelete();
}

void GameObject::removeFromGame() {
	VBE_ASSERT(inGame, "Removing an object from the game that is not in game.");
	inGame = false;
	Game::i()->objectTasksToRemove.push(this);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->removeFromGame();
}

void GameObject::addToGame() {
	VBE_ASSERT(!inGame, "Adding an object to the game that is already in game.");
	inGame = true;
	Game::i()->objectTasksToAdd.push(this);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->addToGame();
}
