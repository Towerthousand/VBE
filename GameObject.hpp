#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class GameObject { //scenegraph nodes
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(float deltaTime);
		virtual void draw() const;
		virtual void addObject(GameObject* object);
		void setName(std::string newName);
		void setDrawPriority(int newPriority);
		int getDrawPriority();
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
		static int getObjectCount();

		const int id;
		bool isAlive;
	protected:
		GameObject* parent;
		std::list<GameObject*> children;
		mat4f transform;
		mat4f fullTransform;
	private:
		void calcFullTransform(mat4f parentFullTransform);
		void doUpdate(float deltaTime);
		int drawPriority;
		std::string name;

		static int idCounter;
		static int objectCount;
		static std::map<std::string,GameObject*> nameMap;
		static std::map<int,GameObject*> idMap;

		friend class Game;

	public:
		// debug function. Checks all nodes are childs of their parents (only once)
		// and that not more than one null parent exists (the root object)
		static bool checkTree(GameObject* root, int& nulls);

};

#endif // GAMEOBJECT_HPP
