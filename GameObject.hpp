#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class Game;
class ContainerObject;
class GameObject { //scenegraph nodes
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(float deltaTime);
		virtual void draw() const ;

		void addTo(GameObject* parent);
		void removeAndDelete();

		void setName(std::string newName);
		std::string getName() const;
		int getDrawPriority() const;
		int getUpdatePriority() const;
		void setDrawPriority(int newPriority);
		void setUpdatePriority(int newPriority);

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

		const std::list<GameObject*>& getChildren() const;

		const int id;
	protected:
		Game* getGame() const;
		const GameObject* getParent() const;
		virtual void onObjectAdd(GameObject* object);

		//Model matrix
		mat4f transform;
		mat4f fullTransform;
	private:
		void removeFromParent();
		void propragateTransforms();
		void markForDelete();

		virtual void addToContainer(GameObject* obj);
		virtual void removeFromContainer(GameObject* obj);

		GameObject* parent;
		std::list<GameObject*> children;
		int drawPriority;
		int updatePriority;
		std::string name;
		ContainerObject* container;
		bool isAlive;

		friend class Game;
		friend class ContainerObject;
};

#endif // GAMEOBJECT_HPP
