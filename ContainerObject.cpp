#include "ContainerObject.hpp"

ContainerObject::ContainerObject()
{
}


// Update scenegraph
void ContainerObject::update(float deltaTime) {

	while(!objectTasksToRemove.empty()) {
		GameObject* obj = objectTasksToRemove.front();
		updateTasks.erase(obj);
		drawTasks.erase(obj);
		objectTasksToRemove.pop();
		if(!obj->isAlive) delete obj;
	}

	while(!objectTasksToAdd.empty()) {
		GameObject* obj = objectTasksToAdd.front();
		updateTasks.insert(obj);
		drawTasks.insert(obj);
		objectTasksToAdd.pop();
	}

	for(std::set<GameObject*,FunctorCompareUpdate>::iterator it = updateTasks.begin(); it != updateTasks.end(); ++it)
		(*it)->update(deltaTime);
}

// Draw scenegraph
void ContainerObject::draw() {
	propragateTransforms();
	for(std::set<GameObject*,FunctorCompareDraw>::iterator it = drawTasks.begin(); it != drawTasks.end(); ++it)
		(*it)->draw();
}


void ContainerObject::addToContainer(GameObject* obj) {
	VBE_ASSERT(!obj->inContainer, "Adding an object to container that is already in a container.");
	obj->inContainer = true;
	objectTasksToAdd.push(obj);
	for(std::list<GameObject*>::iterator it = obj->children.begin(); it != obj->children.end(); ++it)
		addToContainer(*it);
}


void ContainerObject::removeFromContainer(GameObject* obj) {
	VBE_ASSERT(obj->inContainer, "Removing an object from a container that is not in a container.");
	obj->inContainer = false;
	objectTasksToRemove.push(obj);
	for(std::list<GameObject*>::iterator it = obj->children.begin(); it != obj->children.end(); ++it)
		removeFromContainer(*it);
}
