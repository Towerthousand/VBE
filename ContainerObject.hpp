#ifndef CONTAINEROBJECT_HPP
#define CONTAINEROBJECT_HPP

#include "GameObject.hpp"

class ContainerObject : public GameObject {
	public:
		ContainerObject();

		struct FunctorCompareDraw{
				bool operator()(const GameObject* a, const GameObject* b) {
					if(a->drawPriority == b->drawPriority)
						return (a->id < b->id);
					return (a->drawPriority < b->drawPriority);
				}
		};
		struct FunctorCompareUpdate{
				bool operator()(const GameObject* a, const GameObject* b) {
					if(a->updatePriority == b->updatePriority)
						return (a->id < b->id);
					return (a->updatePriority < b->updatePriority);
				}
		};

		virtual void update(float deltaTime);
		virtual void draw();

	private:
		virtual void addToContainer(GameObject* obj);
		virtual void removeFromContainer(GameObject* obj);

		std::set<GameObject*, FunctorCompareDraw> drawTasks;
		std::set<GameObject*, FunctorCompareUpdate> updateTasks;

		std::queue<GameObject*> objectTasksToAdd;
		std::queue<GameObject*> objectTasksToRemove;

		friend class GameObject;
		friend class Game;
};

#endif // CONTAINEROBJECT_HPP
