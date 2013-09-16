#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class GameObject { //Static objects that have a position and rotation but don't move
	public:
		GameObject(GameObject* parent, const vec3f &pos, const vec3f &scale, std::string ID = "");
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
		static GameObject* getObjectByID(std::string ID);

		bool isAlive;
		vec3f pos;
		vec3f scale;
	protected:
		GameObject* parent;
		std::list<GameObject*> children;
	private:
		std::string id;
		static std::map<std::string,GameObject*> IDmap;

};

#endif // GAMEOBJECT_HPP
