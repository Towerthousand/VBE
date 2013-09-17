#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class GameObject { //scenegraph nodes
	public:
		GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale);
		virtual ~GameObject();

		virtual void update(float deltaTime);
		virtual void draw() const;
		virtual void addObject(GameObject* object);
		void setName(std::string newName);
		std::string getName();

		template<class T>
		void getAllObjectsOfType(std::vector<T*> &v) {
			T* p = dynamic_cast<T*>(this);
			if(p) v.push_back(p);
			for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
				(*it)->getAllObjectsOfType<T>(v);
		}

		template<class T>
		T* getFirstObjectOfType() {
			T* p = dynamic_cast<T*>(this);
			if(p) return p;
			for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it) {
				p = (*it)->getFirstObjectOfType<T>();
				if(p) return p;
			}
			return NULL;
		}
		static GameObject* getObjectByName(std::string name);
		static GameObject* getObjectByID(int id);

		vec3f pos;
		vec3f scale;
		const int id;
		bool isAlive;
	protected:
		GameObject* parent;
		std::list<GameObject*> children;
	private:
		void doUpdate(float deltaTime);
		void doDraw();
		std::string name;
		static int idCounter;
		static std::map<std::string,GameObject*> nameMap;
		static std::map<int,GameObject*> idMap;

		friend class Game;
};

#endif // GAMEOBJECT_HPP
