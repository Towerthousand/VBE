#ifndef REGULARPOLYGONOBJECT_HPP
#define REGULARPOLYGONOBJECT_HPP
#include "../GameObject.hpp"
#include "../graphics/Model.hpp"

class RegularPolygonObject : public GameObject {
	public:
		RegularPolygonObject(GameObject* m_parent, const vec3f &m_pos, const vec3f &m_scale, unsigned int sides);
		~RegularPolygonObject();

		void update(float deltaTime);
		void updateMatrix();
		void draw() const;
	private:
		Model m_poly;
};

#endif // REGULARPOLYGONOBJECT_HPP
