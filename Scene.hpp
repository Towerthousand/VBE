#ifndef SCENE_HPP
#define SCENE_HPP
#include "tools.hpp"
#include "GameObject.hpp"

struct RenderState {
		RenderState() : model(1.0f), view(1.0f), projection(1.0f) {}
		~RenderState() {}
		mat4f model,view,projection;
};

class Game;
class Scene : public GameObject{ //abstract
	public:
		Scene(Game &parent); //should NOT do anything apart from being called
		virtual ~Scene();

		virtual void update(float deltaTime) = 0; //called by parent on parent.update()
		virtual void draw() const = 0; //called by parent on parent.draw()
		virtual void addObject(GameObject* object);

		RenderState &getState() const;
	protected:
		virtual bool loadResources() = 0; //load stuff with managers

		Game& parent;
		mutable RenderState state;
		std::list<GameObject*> objects;
};

#endif // SCENE_HPP
