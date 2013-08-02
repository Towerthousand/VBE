#ifndef HITBOX_HPP
#define HITBOX_HPP
#include "tools.hpp"

class GameObject;
class Hitbox {
	public:
		enum hitboxType {
			BOX = 0,
			POINT
		};

		Hitbox(GameObject* parent, hitboxType type, const vec3f &radius = vec3f(0,0,0));
		~Hitbox();

		bool collidesWithWorld( const vec3f &offset = vec3f(0,0,0)) const;
		bool collidesWithHitbox(const Hitbox& hitbox, const vec3f &offset = vec3f(0,0,0)) const;
		void draw() const;

		vec3f radius;
		hitboxType type;

	private:
		bool pointCollidesWithWorld(const vec3f& point) const;

		GameObject* parent;
		static const int vertexPoints[8][3];
		static const int indexes[24];
};

#endif // HITBOX_HPP
