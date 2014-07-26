#ifndef LISTENER_HPP
#define LISTENER_HPP
#include "tools.hpp"

class Listener {
	public :
		static void setGlobalVolume(float volume);
		static float getGlobalVolume();
		static void setPosition(float x, float y, float z);
		static void setPosition(const vec3f& position);
		static vec3f getPosition();
		static void setDirection(float x, float y, float z);
		static void setDirection(const vec3f& direction);
		static vec3f getDirection();
		static void setUpVector(float x, float y, float z);
		static void setUpVector(const vec3f& upVector);
		static vec3f getUpVector();
};

#endif // LISTENER_HPP
