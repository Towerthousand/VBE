#ifndef TEXTUREDOBJECT_HPP
#define TEXTUREDOBJECT_HPP
#include "../GameObject.hpp"
#include "../graphics/Model.hpp"

class TexturedObject : public GameObject {
	public:
		TexturedObject(GameObject* m_parent, const vec3f &m_pos, const vec3f &m_scale);
		~TexturedObject();

		void update(float deltaTime);
		void updateMatrix();
		void draw() const;
	private:
		Model m_tri;
};

#endif // TEXTUREDOBJECT_HPP
