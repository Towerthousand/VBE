#ifndef TRIANGLEOBJECT_HPP
#define TRIANGLEOBJECT_HPP
#include "../GameObject.hpp"
#include "../graphics/Model.hpp"

class TriangleObject : public GameObject {
	public:
		TriangleObject(Scene* parentScene, ShaderProgram* program, vec3f pos, vec3f scale);
		virtual ~TriangleObject();

		void update(float deltaTime);
		void updateMatrix();
		void draw() const;
	private:
		Model tri;
};

#endif // TRIANGLEOBJECT_HPP
