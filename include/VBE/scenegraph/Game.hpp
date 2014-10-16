#ifndef GAME_HPP
#define GAME_HPP

#include<map>

#include <VBE/scenegraph/GameObject.hpp>
#include <VBE/scenegraph/ContainerObject.hpp>

class Game : public ContainerObject {
	public:
		Game();
		virtual ~Game();
		static Game* i() { return Game::instance;}

		GameObject* getObjectByName(std::string name) const;
		GameObject* getObjectByID(int id) const;

		virtual void run();

		void setFixedUpdateRate(int fixedUpdateRate);
		void setDynamicFramerate();

		bool isRunning;
	protected:
		virtual void update(float deltaTime);
		virtual void draw();
	private:
		std::map<std::string, GameObject*> nameMap;
		std::map<int, GameObject*> idMap;
		int idCounter;

		int fixedUpdateRate;
		bool isFixedUpdateRate;

		static Game* instance;

		friend class GameObject;
		friend class ContainerObject;
};

#endif //GAME_HPP
