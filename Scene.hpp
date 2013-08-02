#ifndef SCENE_HPP
#define SCENE_HPP
#include "tools.hpp"

class Game;
class RenderState;
class InputManager;
class TextureManager;
class FontManager;
class AudioManager;
class Scene { //abstract
	public:
		Scene(Game &parent); //should NOT do anything apart from being called
		virtual ~Scene();
		virtual bool init() = 0; //should call loadResources()
		virtual void update(float deltaTime) = 0; //called by parent on parent.update()
		virtual void draw() const = 0; //called by parent on parent.draw()
		virtual void onKeyPressed(float deltaTime, sf::Keyboard::Key key) = 0; //called by parent on parent.update()
		virtual void onKeyDown(float deltaTime, sf::Keyboard::Key key) = 0; //called by parent on parent.update()
		virtual void onKeyReleased(float deltaTime, sf::Keyboard::Key key) = 0; //called by parent on parent.update()
		virtual void onMouseButtonPressed(float deltaTime, sf::Mouse::Button button) = 0; //called by parent on parent.update()
		virtual void onMouseButtonDown(float deltaTime, sf::Mouse::Button button) = 0; //called by parent on parent.update()
		virtual void onMouseButtonReleased(float deltaTime, sf::Mouse::Button button) = 0; //called by parent on parent.update()
		virtual void onMouseMoved(float deltaTime, int dx, int dy) = 0; //called by parent on parent.update()
		virtual void onClose() = 0; //close scene-wide stuff

		InputManager &getInputs() const;
		TextureManager &getTextures() const;
		FontManager &getFonts() const;
		AudioManager &getAudios() const;
		RenderState &getState() const;
	protected:
		Game& parent;
		virtual bool loadResources() = 0; //load stuff with managers
};

#endif // SCENE_HPP
