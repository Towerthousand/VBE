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
		static bool init();
		static void run();
		static void setRoot(GameObject* newRoot);
		static void close();

		static sf::RenderWindow &getWindow() { return window; }
		
		static bool isRunning;
	private:
		static void update(float deltaTime);
		static void draw();
		static bool loadResources ();

		static sf::RenderWindow window;
		static GameObject* root;

//		struct drawTask {
//				RenderState::RenderInstance state;
//				GameObject* node;
//		};
//      static std::priority_queue<..> drawTasks;

		Game();
		~Game();
};

#endif //GAME_HPP
