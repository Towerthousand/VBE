#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP
#include "../GameObject.hpp"

class Game;
class SceneMain : public GameObject {
	public:
		SceneMain();
		~SceneMain();
		void update(float deltaTime);

	private:
		bool loadResources();
		float debugCounter;
		int fpsCount;
};

#endif // SCENEMAIN_HPP
