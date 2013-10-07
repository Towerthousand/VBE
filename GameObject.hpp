#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class Game;
class GameObject { //scenegraph nodes
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(float deltaTime);
		virtual void draw() const ;

		void addTo(GameObject* parent);
		void removeFromParent();
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

		const std::list<GameObject*>& getChildren() const {
			return children;
		}

		Game* getGame() const {
			return game;
		}

		const int id;
	protected:
		virtual void onObjectAdd(GameObject* object);

		mat4f transform;
		mat4f fullTransform;

	private:
		Game* game;
		bool inGame;
		GameObject* parent;
		std::list<GameObject*> children;

		int drawPriority;
		int updatePriority;
		std::string name;
		bool isAlive;

		void calcFullTransform(mat4f parentFullTransform);
		void markForDelete();
		void addToGame();
		void removeFromGame();

		friend class Game;

	public:
		// debug function. Checks all nodes are childs of their parents (only once)
		// and that not more than one null parent exists (the root object)
		static bool checkTree(GameObject* root, int& nulls);

};

#endif // GAMEOBJECT_HPP
