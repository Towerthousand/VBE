#include "Listener.hpp"
#include "ALCheck.hpp"

float Listener::listenerVolume(100.f);
vec3f Listener::listenerPosition(0.f, 0.f, 0.f);
vec3f Listener::listenerDirection(0.f, 0.f, -1.f);
vec3f Listener::listenerUpVector(0.f, 1.f, 0.f);

void Listener::setGlobalVolume(float volume) {
	if (volume != listenerVolume) {
		ensureALInit();

		alCheck(alListenerf(AL_GAIN, volume * 0.01f));
		listenerVolume = volume;
	}
}

float Listener::getGlobalVolume() {
	return listenerVolume;
}

void Listener::setPosition(float x, float y, float z) {
	setPosition(vec3f(x, y, z));
}

void Listener::setPosition(const vec3f& position) {
	if (position != listenerPosition) {
		ensureALInit();

		alCheck(alListener3f(AL_POSITION, position.x, position.y, position.z));
		listenerPosition = position;
	}
}

vec3f Listener::getPosition() {
	return listenerPosition;
}

void Listener::setDirection(float x, float y, float z) {
	setDirection(vec3f(x, y, z));
}

void Listener::setDirection(const vec3f& direction) {
	if (direction != listenerDirection) {
		ensureALInit();

		float orientation[] = {direction.x, direction.y, direction.z, listenerUpVector.x, listenerUpVector.y, listenerUpVector.z};
		alCheck(alListenerfv(AL_ORIENTATION, orientation));
		listenerDirection = direction;
	}
}

vec3f Listener::getDirection() {
	return listenerDirection;
}

void Listener::setUpVector(float x, float y, float z) {
	setUpVector(vec3f(x, y, z));
}

void Listener::setUpVector(const vec3f& upVector) {
	if (upVector != listenerUpVector) {
		ensureALInit();

		float orientation[] = {listenerDirection.x, listenerDirection.y, listenerDirection.z, upVector.x, upVector.y, upVector.z};
		alCheck(alListenerfv(AL_ORIENTATION, orientation));
		listenerUpVector = upVector;
	}
}

vec3f Listener::getUpVector() {
	return listenerUpVector;
}
