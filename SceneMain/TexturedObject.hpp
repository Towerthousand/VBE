#ifndef TEXTUREDOBJECT_HPP
#define TEXTUREDOBJECT_HPP
#include "../GameObject.hpp"
#include "../graphics/Model.hpp"

class TexturedObject : public GameObject {
	public:
		TexturedObject(GameObject* parent, const vec3f &pos, const vec3f &scale);
		~TexturedObject();

		void update(float deltaTime);
		void updateMatrix();
		void draw() const;

		vec3f pos;
		vec3f scale;
	private:
		Model tri;
};

#endif // TEXTUREDOBJECT_HPP
