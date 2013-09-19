#include "GameObject.hpp"
#include "RenderState.hpp"
#include "Game.hpp"

std::map<std::string,GameObject*> GameObject::s_nameMap;
std::map<int,GameObject*> GameObject::s_idMap;
int GameObject::s_idCounter = 1;
int GameObject::s_objectCount = 0;

GameObject::GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale) :
	m_pos(pos), m_scale(scale), m_id(s_idCounter++), m_isAlive(true),
	m_parent(parent), m_drawPriority(0), m_name("") {
	++s_objectCount;
	s_idMap.insert(std::pair<int,GameObject*>(m_id,this));
}

GameObject::~GameObject() {
	--s_objectCount;
	for(std::list<GameObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		delete *it;
	if(!m_name.empty())
		s_nameMap.erase(m_name);
	s_idMap.erase(m_id);
}

void GameObject::update(float deltaTime) {
	(void) deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addObject(GameObject *object) {
	m_children.push_back(object);
	object->setDrawPriority(m_drawPriority);
}

void GameObject::setName(std::string newName) {
	if(s_nameMap.insert(std::pair<std::string,GameObject*>(newName,this)).second) {
		if(!m_name.empty()) s_nameMap.erase(m_name);
		m_name = newName;
	}
}

void GameObject::setDrawPriority(int newPriority) {
	VBE_ASSERT(newPriority >= m_drawPriority || m_parent == NULL || m_parent->getDrawPriority() <= newPriority,
			   "Invalid priority for gameobject with id " << this->m_id)
	m_drawPriority = newPriority;
	for(std::list<GameObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->setDrawPriority(newPriority);
}

int GameObject::getDrawPriority() {
	return m_drawPriority;
}

std::string GameObject::getName() {
	return m_name;
}

GameObject* GameObject::getObjectByName(std::string name) {
	return s_nameMap.at(name);
}

GameObject* GameObject::getObjectByID(int id) {
	return s_idMap.at(id);
}

int GameObject::getObjectCount() {
	return s_objectCount;
}

void GameObject::doUpdate(float deltaTime) {
	update(deltaTime);
	for(std::list<GameObject*>::iterator it = m_children.begin(); it != m_children.end();) {
		(*it)->doUpdate(deltaTime);
		if (!(*it)->m_isAlive) {
			delete *it;
			it = m_children.erase(it);;
		}
		else
			++it;
	}
}

void GameObject::doDraw() {
	VBE_ASSERT(m_drawPriority >= Game::s_drawLayer, "Draw priority is messed up. Internal error (?). Object id: " << this->m_id)
	if(m_drawPriority == Game::s_drawLayer) {
		RenderState::push();
		this->draw();
		for(std::list<GameObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
			(*it)->doDraw();
		RenderState::pop();
	}
	else {
		RenderState::RenderInstance currState = RenderState::getCurrent();
		Game::addDrawTask(currState,this);
	}
}
