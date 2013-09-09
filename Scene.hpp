#ifndef SCENE_HPP
#define SCENE_HPP
#include "tools.hpp"

class Game;
class RenderState;
class InputManager;
class TextureManager;
class AudioManager;
class Scene { //abstract
	public:
		Scene(Game &parent); //should NOT do anything apart from being called
		virtual ~Scene();

		virtual void update(float deltaTime) = 0; //called by parent on parent.update()
		virtual void draw() const = 0; //called by parent on parent.draw()

		InputManager &getInputs() const;
		TextureManager &getTextures() const;
		AudioManager &getAudios() const;
		RenderState &getState() const;
	protected:
		Game& parent;
		virtual bool loadResources() = 0; //load stuff with managers
};

#endif // SCENE_HPP
