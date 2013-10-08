#include "GameObject.hpp"
#include "Game.hpp"

GameObject::GameObject() : id(Game::i()->idCounter++),
	transform(1.0f), fullTransform(1.0), game(Game::i()), inGame(false), parent(NULL), drawPriority(0),
	updatePriority(0), name(""), isAlive(true) {
	game->idMap.insert(std::pair<int,GameObject*>(id,this));
}

GameObject::~GameObject() {
	if(game != NULL) {
		if(!name.empty())
			game->nameMap.erase(name);
		game->idMap.erase(id);
	}
}

void GameObject::update(float deltaTime) {
	(void)deltaTime;
}

void GameObject::draw() const {

}


void GameObject::addTo(GameObject *newParent) {
	VBE_ASSERT(parent == NULL, "Trying to attach a node that is already attached.");
	parent = newParent;
	parent->children.push_back(this);
	parent->onObjectAdd(this);
	if(parent->inGame)
		addToGame();
}

void GameObject::removeFromParent() {
	VBE_ASSERT(parent != NULL, "Trying to detach a not attached node.");
	parent->children.remove(this);
	if(parent->inGame)
		removeFromGame();
	parent = NULL;
}

void GameObject::removeAndDelete() {
	removeFromParent();
	markForDelete();
}

void GameObject::markForDelete() {
	isAlive = false;
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->markForDelete();
}

void GameObject::addToGame() {
	VBE_ASSERT(!inGame, "Adding an object to the game that is already in game.");
	inGame = true;
	game->objectTasksToAdd.push(this);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->addToGame();
}

void GameObject::removeFromGame() {
	VBE_ASSERT(inGame, "Removing an object from the game that is not in game.");
	inGame = false;
	game->objectTasksToRemove.push(this);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->removeFromGame();
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
	VBE_ASSERT(!inGame, "You can't change the priority of an object that is in the game.");
	if(drawPriority == newPriority) return;
	drawPriority = newPriority;
}

void GameObject::setUpdatePriority(int newPriority) {
	VBE_ASSERT(!inGame, "You can't change the priority of an object that is in the game.");
	if(updatePriority == newPriority) return;
	updatePriority = newPriority;
}

std::string GameObject::getName() const {
	return name;
}

int GameObject::getDrawPriority() const {
	return drawPriority;
}

int GameObject::getUpdatePriority() const {
	return updatePriority;
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
