#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP
#include "Scene.hpp"

class GameObject;
class ShaderProgram;
class SceneMain : public Scene {
	public:
		//virtual overrides
		SceneMain(Game &parent);
		~SceneMain();

		void update(float deltaTime);
		void draw() const;

		void addObject(GameObject* object);

		ShaderProgram* shaderExample; //I have not done a shader manager yet :/
        ShaderProgram* shaderExample2;

	private:
		bool loadResources();

		std::list<GameObject*> objects;
		float debugCounter;
		int fpsCount;
};

#endif // SCENEMAIN_HPP
