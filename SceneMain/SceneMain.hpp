#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP
#include "../Scene.hpp"

class GameObject;
class ShaderProgram;
class SceneMain : public Scene {
	public:
		//virtual overrides
		SceneMain(Game &parent);
		~SceneMain();

		void update(float deltaTime);
		void draw() const;

	private:
		bool loadResources();
		float debugCounter;
		int fpsCount;
};

#endif // SCENEMAIN_HPP
