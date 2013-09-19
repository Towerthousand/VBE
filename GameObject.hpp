#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class GameObject { //scenegraph nodes
	public:
		GameObject(GameObject* m_parent, const vec3f &pos, const vec3f &scale);
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
			for(std::list<GameObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
				(*it)->getAllObjectsOfType<T>(v);
		}

		template<class T>
		T* getFirstObjectOfType() {
			T* p = dynamic_cast<T*>(this);
			if(p) return p;
			for(std::list<GameObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it) {
				p = (*it)->getFirstObjectOfType<T>();
				if(p) return p;
			}
			return NULL;
		}
		static GameObject* getObjectByName(std::string m_name);
		static GameObject* getObjectByID(int m_id);
		static int getObjectCount();

		vec3f m_pos;
		vec3f m_scale;
		const int m_id;
		bool m_isAlive;
	protected:
		GameObject* m_parent;
		std::list<GameObject*> m_children;
	private:
		void doUpdate(float deltaTime);
		void doDraw();
		int m_drawPriority;
		std::string m_name;
		static int s_idCounter;
		static int s_objectCount;
		static std::map<std::string,GameObject*> s_nameMap;
		static std::map<int,GameObject*> s_idMap;

		friend class Game;
};

#endif // GAMEOBJECT_HPP
