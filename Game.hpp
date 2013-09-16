#ifndef GAME_HPP
#define GAME_HPP

#include "graphics/TextureManager.hpp"
#include "graphics/MeshManager.hpp"
#include "graphics/ShaderManager.hpp"
#include "audio/AudioManager.hpp"
#include "input/InputManager.hpp"
#include "RenderState.hpp"
#include "GameObject.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Model.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Uniform.hpp"

class Game {
	public:
		Game();
		~Game();
		bool init();
		void run();
		void setRoot(GameObject* newRoot);

		sf::RenderWindow &getWindow() { return window; }
		
		bool isRunning;
	private:
		void update(float deltaTime);
		void draw();
		bool loadResources ();

		sf::RenderWindow window;
		GameObject* root;
};

#endif //GAME_HPP
