#ifndef GAME_HPP
#define GAME_HPP

#include "audio/AudioManager.hpp"
#include "input/Input.hpp"
#include "GameObject.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Model.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Uniform.hpp"

class Game {
		struct FunctorCompareDraw{
				bool operator()(const GameObject* a, const GameObject* b) {
					if(a->drawPriority == b->drawPriority)
						return (a->id > b->id);
					return (a->drawPriority > b->drawPriority);
				}
		};
		struct FunctorCompareUpdate{
				bool operator()(const GameObject* a, const GameObject* b) {
					if(a->updatePriority == b->updatePriority)
						return (a->id > b->id);
					return (a->updatePriority > b->updatePriority);
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
		static std::set<GameObject*,FunctorCompareDraw> drawTasks;
		static std::set<GameObject*,FunctorCompareUpdate> updateTasks;

		friend class GameObject;

		Game();
		~Game();
};

#endif //GAME_HPP
