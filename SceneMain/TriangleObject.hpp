#ifndef TRIANGLEOBJECT_HPP
#define TRIANGLEOBJECT_HPP
#include "GameObject.hpp"
#include "../graphics/Model.hpp"

class TriangleObject : public GameObject {
	public:
		TriangleObject(SceneMain* parentScene, vec3f pos, vec3f scale);
		~TriangleObject();

		void update(float deltaTime);
		void updateMatrix();
		void draw() const;
	private:
		Model tri;
};

#endif // TRIANGLEOBJECT_HPP
