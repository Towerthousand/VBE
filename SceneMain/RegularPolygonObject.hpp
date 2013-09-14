#ifndef REGULARPOLYGONOBJECT_HPP
#define REGULARPOLYGONOBJECT_HPP
#include "../GameObject.hpp"
#include "../graphics/Model.hpp"

class RegularPolygonObject : public GameObject {
	public:
		RegularPolygonObject(Scene* parentScene, const vec3f &pos, const vec3f &scale, unsigned int sides);
		virtual ~RegularPolygonObject();

		void update(float deltaTime);
		void updateMatrix();
		void draw() const;
	private:
		Model poly;
};

#endif // REGULARPOLYGONOBJECT_HPP
