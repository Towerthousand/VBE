#ifndef GAME_HPP
#define GAME_HPP

#include "graphics/TextureManager.hpp"
#include "graphics/MeshManager.hpp"
#include "graphics/ShaderManager.hpp"
#include "audio/AudioManager.hpp"
#include "input/InputManager.hpp"
#include "GameObject.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Model.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Uniform.hpp"

class Game {
		struct FunctorCompare{
				bool operator()(const std::pair<int,GameObject*> &a, const std::pair<int,GameObject*> &b) {
					if(a.first == b.first)
						return (a.second > b.second);
					return (a.first > b.first);
				}
		};
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
		static std::set<std::pair<int,GameObject*>,FunctorCompare> drawTasks;

		friend class GameObject;

		Game();
		~Game();
};

#endif //GAME_HPP
