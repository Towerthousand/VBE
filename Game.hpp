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
		struct DrawTask {
				DrawTask(RenderState::RenderInstance state, GameObject* object)
					: state(state), object(object) {}
				~DrawTask() {}
				RenderState::RenderInstance state;
				GameObject* object;
		};
		struct FunctorCompare{
				bool operator()(const std::pair<int,DrawTask> &a, const std::pair<int,DrawTask> &b) {
					return (a.first < b.first);
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

		static void addDrawTask(RenderState::RenderInstance state, GameObject* object);
		static int drawLayer;
		static sf::RenderWindow window;
		static GameObject* root;
		static std::priority_queue<std::pair<int,DrawTask>,std::vector<std::pair<int,DrawTask>>,FunctorCompare> priorityDraws;

		friend class GameObject;

		Game();
		~Game();
};

#endif //GAME_HPP
