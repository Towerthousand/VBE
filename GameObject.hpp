#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class Scene;class GameObject { //Static objects that have a position and rotation but don't move
	public:
		GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale);
		virtual ~GameObject();

		virtual void update(float deltaTime);
		virtual void draw() const;
		virtual void addObject(GameObject* object);

		template<class T>
		void getObjectsByType(std::vector<T*> &v) {
			T* p = dynamic_cast<T*>(this);
			if(p) v.push_back(p);
			for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
				(*it)->getObjectsByType<T>(v);
		}

		bool isAlive;
		vec3f pos;
		vec3f scale;
	protected:
		GameObject* parent;
		std::list<GameObject*> children;
};

#endif // GAMEOBJECT_HPP
