#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP
#include "../GameObject.hpp"

class Game;
class SceneMain : public GameObject {
	public:
		SceneMain(Game &parent);
		~SceneMain();

		void update(float deltaTime);
		void draw() const;

	private:
		bool loadResources();
		float debugCounter;
		int fpsCount;
		Game& parentGame;
};

#endif // SCENEMAIN_HPP
