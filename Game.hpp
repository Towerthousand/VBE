#ifndef GAME_HPP
#define GAME_HPP
#include "ContainerObject.hpp"

class Game : public ContainerObject {
	public:
		Game();
		virtual ~Game();

		GameObject* getObjectByName(std::string name) const;
		GameObject* getObjectByID(int id) const;

		virtual void run();
		virtual void update(float deltaTime);
		virtual void draw();

		int getObjectCount() const { return updateTasks.size(); }
		sf::RenderWindow &getWindow() { return window; }
		
		bool isRunning;
	private:
		static Game* i() { return Game::instance;}

		sf::RenderWindow window;

		std::map<std::string, GameObject*> nameMap;
		std::map<int, GameObject*> idMap;
		int idCounter;

		static Game* instance;

		friend class GameObject;
		friend class ContainerObject;
};

#endif //GAME_HPP
