#include <VBE/scenegraph/GameObject.hpp>
#include <VBE/scenegraph/Game.hpp>
#include <VBE/system/Log.hpp>

GameObject::GameObject() : id(Game::i() != nullptr?Game::i()->idCounter++:-1),
	transform(1.0f), fullTransform(1.0f), parent(nullptr), drawPriority(0),
	updatePriority(0), name(""), container(nullptr), isAlive(true) {
	if(Game::i() != nullptr)
		Game::i()->idMap.insert(std::pair<int, GameObject*>(id, this));
}

GameObject::~GameObject() {
	//erase traces from the object
	if(Game::i() != nullptr) {
		if(!name.empty())
			Game::i()->nameMap.erase(name);
		Game::i()->idMap.erase(id);
	}
}

void GameObject::update(float deltaTime) {
	(void)deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addTo(GameObject *newParent) {
	//Called whenever we want to add an object to a parent object
	VBE_ASSERT(parent == nullptr, "Trying to attach a node that is already attached.");
	parent = newParent;
	parent->children.push_back(this);
	parent->onObjectAdd(this);

	if(parent->container != nullptr || dynamic_cast<ContainerObject*>(parent) != nullptr)
		parent->addToContainer(this);
}

void GameObject::removeAndDelete() {
	//This will remove the object from the tree and it will tell the game to stop tracking
	//these objects and delete them.
	removeFromParent();
	markForDelete();
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

void GameObject::setName(std::string newName) {
	if(name == newName || Game::i() == nullptr) return;
	if(Game::i()->nameMap.insert(std::pair<std::string, GameObject*>(newName, this)).second) {
		if(!name.empty()) Game::i()->nameMap.erase(name);
		name = newName;
	}
	else {VBE_ASSERT(false, "Can't set name " << newName << " for node " << this << ". This name is already in use." );}
}

void GameObject::setDrawPriority(int newPriority) {
	if(drawPriority == newPriority) return;
	if(parent != nullptr) {
		container->objectTasksToRemove.push(this);
		container->objectTasksToAdd.push(this);
	}
	drawPriority = newPriority;
}

void GameObject::setUpdatePriority(int newPriority) {
	if(updatePriority == newPriority) return;
	if(container != nullptr) {
		container->objectTasksToRemove.push(this);
		container->objectTasksToAdd.push(this);
	}
	updatePriority = newPriority;
}

mat4f GameObject::getFullTransform() const
{
	return fullTransform;
}

const std::list<GameObject*>& GameObject::getChildren() const {
	return children;
}

Game* GameObject::getGame() const {
	return Game::i();
}

const GameObject* GameObject::getParent() const {
	return parent;
}

void GameObject::onObjectAdd(GameObject* object) {
	(void)object;
}

void GameObject::removeFromParent() {
	VBE_ASSERT(parent != nullptr, "Trying to detach a not attached node.");
	parent->children.remove(this);
	if(container != nullptr)
		parent->removeFromContainer(this);
	parent = nullptr;
}

void GameObject::propragateTransforms() const{
	if(parent == nullptr)
		fullTransform = transform;
	else
		fullTransform = parent->fullTransform * transform;

	for(std::list<GameObject*>::const_iterator it = children.begin(); it != children.end(); ++it)
		(*it)->propragateTransforms();
}

void GameObject::markForDelete() {
	isAlive = false;
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->markForDelete();
}

void GameObject::addToContainer(GameObject* obj) {
	if(parent != nullptr)
		parent->addToContainer(obj);
}


void GameObject::removeFromContainer(GameObject* obj) {
	if(parent != nullptr)
		parent->removeFromContainer(obj);
}
