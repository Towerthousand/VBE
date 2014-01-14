#ifndef GAME_HPP
#define GAME_HPP
#include "ContainerObject.hpp"

class Game : public ContainerObject {
	public:
		Game();
		virtual ~Game();
		static Game* i() { return Game::instance;}

		const GameObject* getObjectByName(std::string name) const;
		const GameObject* getObjectByID(int id) const;
		GameObject* getObjectByName(std::string name);
		GameObject* getObjectByID(int id);

		virtual void run();
		virtual void update(float deltaTime);
		virtual void draw();

		sf::RenderWindow &getWindow() { return window; }
		
		bool isRunning;
	private:
		sf::RenderWindow window;

		std::map<std::string, GameObject*> nameMap;
		std::map<int, GameObject*> idMap;
		int idCounter;

		static Game* instance;

		friend class GameObject;
		friend class ContainerObject;
};

#endif //GAME_HPP
