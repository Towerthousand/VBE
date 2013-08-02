#ifndef GAME_HPP
#define GAME_HPP

//	THIS IS THE SFML BINDING OF MY ENGINE. DESIGNED TO WORK ON IT'S OWN CLASS. USAGE:
//	 - Create a class MyScene that inherits from Scene.hpp
//	   It has all types of methods for input & game loop: Key & Mouse input,
//	   Update for logic, Draw for openGL and SFML calls to draw, init, loadResources
//	   to load stuff (use the managers as to load) and an onClose method. It is pretty
//	   straightforward.
//   - Then, on main, just do this:
//
//	#include "Game.hpp"
//  #include "MyScene.hpp"
//
//	int main() {
//		Game myGame;
//		if(myGame.init()) {
//			myGame.setScene(new MyScene(myGame));
//			myGame.run();
//		}
//		return 0;
//	}
//   - It will run right off the bat. Screen size is set to fullscreen (max resolution
//     available), but you can tweak that in Game::Game() and tools.cpp


#include "graphics/TextureManager.hpp"
#include "graphics/FontManager.hpp"
#include "audio/AudioManager.hpp"
#include "input/InputManager.hpp"
#include "SceneMain/SceneMain.hpp"
#include "RenderState.hpp"

class Game {
	public:
		Game(); //creates window
		~Game();
		bool init(); // inits game-wide stuff here (init and resource loading)
		void run(); // won't run if Game::init() isn't called first
					// contains main loop, calls update() and draw()
		void setScene(Scene * scene); // sets nextScene to scene, which will
									  // move into currentScene on next update()
									  // so that there is no update() of one
									  // scene followed by a draw() method
									  // of a different scene.
		void close(); // closes app completely, closing the current scene (if there is)
					  // first, saves game-wide stuff first.

		sf::RenderWindow &getWindow() { return window; }
		TextureManager &textures() { return texManager; }
		FontManager &font() { return fontManager; }
		AudioManager &audio() { return audioManager; }
		InputManager &input() { return inputManager; }
		RenderState &state() { return renderState; }
		
		bool isRunning;
	private:
		void update(float deltaTime); // changes scene if necessary
									  // updates fps
									  // checks for window events
									  // updates input with
									  // Game::onMouseButtonPressed(); and
									  // Game::onKeyPressed();
									  // calls currentScene.update(deltaTime)
		void draw(); // calls currentScene.draw()
		bool loadResources (); // loads game-wide resources. only called
							   // by init() once
		void onKeyPressed(float deltaTime, const sf::Keyboard::Key &key);
										// currentScene.onKeyPressed
										// (deltaTime, key)
		void onKeyDown(float deltaTime, const sf::Keyboard::Key &key);
										// currentScene.onKeyDown
										// (deltaTime, key)
		void onKeyReleased(float deltaTime, const sf::Keyboard::Key &key);
										// currentScene.onKeyReleased
										// (deltaTime, key)
		void onMouseButtonPressed(float deltaTime, const sf::Mouse::Button &button);
										// currentScene.onMouseButtonPressed
										// (deltaTime, button)
		void onMouseButtonDown(float deltaTime, const sf::Mouse::Button &button);
										// currentScene.onMouseButtonDown
										// (deltaTime, button)
		void onMouseButtonReleased(float deltaTime, const sf::Mouse::Button &button);
										// currentScene.onMouseButtonReleased
										// (deltaTime, button)
		void onMouseMoved(float deltaTime, int dx, int dy);
										// currentScene.onMouseMoved
										// (deltaTime)

		//context
		sf::RenderWindow window;
		Scene* currentScene;
		Scene* nextScene;

		//managers
		TextureManager texManager;
		FontManager fontManager;
		AudioManager audioManager;
		InputManager inputManager;
		RenderState renderState;
};

#endif //GAME_HPP
