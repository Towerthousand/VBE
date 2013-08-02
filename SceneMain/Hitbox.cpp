#include "Hitbox.hpp"
#include "SceneMain.hpp"
#include "GameObject.hpp"

Hitbox::Hitbox(GameObject* parent, hitboxType type, const vec3f &radius) : radius(radius), type(type), parent(parent) {
}

Hitbox::~Hitbox() {
}

bool Hitbox::collidesWithWorld(const vec3f &offset) const {
	switch (type) {
		case (BOX): {
			vec3f newPos = parent->pos + offset;
			for(float x = -radius.x; x <= radius.x+0.3; x += 0.3)
				for(float y = -radius.y; y <= radius.y+0.3; y += 0.3)
					for(float z = -radius.z; z <= radius.z+0.3; z += 0.3) {
						vec3f point(std::fmin(x, radius.x),std::fmin(y, radius.y),std::fmin(z, radius.z));
						if(pointCollidesWithWorld(point+newPos))
							return true;
					}
			break;
		}
		case (POINT):
			return pointCollidesWithWorld(parent->pos+offset);
			break;
		default:
			break;
	}
	return false;
}

bool Hitbox::collidesWithHitbox(const Hitbox &hitbox, const vec3f &offset) const {
	return false; //TODO
}

bool Hitbox::pointCollidesWithWorld(const vec3f& point) const {
	if(parent->parentScene->getWorld()->getCube(floor(point.x),floor(point.y),floor(point.z)).ID != 0)
		return true;
	return false;
}

void Hitbox::draw() const {
//	vec3f drawPos = parent->pos-radius;
//	glPushMatrix();
//	glLineWidth(1.5);
//	glEnableVertexAttribArray(0);
//	glColor4f(0.0,0.0,0.0,0.5);
//	glTranslatef(drawPos.x,drawPos.y,drawPos.z);
//	glScalef(radius.x*2,radius.y*2,radius.z*2);
//	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, &vertexPoints[0]);
//	glDrawElements(GL_LINES,24,GL_UNSIGNED_INT,&indexes[0]);
//	glEnableVertexAttribArray(0);
//	glColor4f(1.0,1.0,1.0,1.0);
//	glPopMatrix();
}

const int Hitbox::vertexPoints[8][3] = {
	{0,0,1},
	{1,0,1},
	{1,1,1},
	{0,1,1},
	{0,0,0},
	{1,0,0},
	{1,1,0},
	{0,1,0}
};

const int Hitbox::indexes[24] = {
	0,1,
	1,2,
	2,3,
	3,0,
	4,5,
	5,6,
	6,7,
	7,4,
	0,4,
	1,5,
	2,6,
	3,7,
};
