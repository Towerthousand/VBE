#include "ParticleEmitter.hpp"
#include "ParticleSystem.hpp"

ParticleEmitter::ParticleEmitter(int particlesPerSecond)
	: oldWorldPos(0.0f), currWorldPos(0.0f),
	  period(1.0f/particlesPerSecond),
	  sys(NULL), state(0.0f) {
	sys = (ParticleSystem*) getGame()->getObjectByName("particleSystem");
}

ParticleEmitter::~ParticleEmitter() {
}

void ParticleEmitter::update(float deltaTime) {
	VBE_ASSERT(period > 0, "Invalid particle emitter period. Period must be bigger than 0.");
	currWorldPos = vec3f(fullTransform*vec4f(0,0,0,1));
	while(state < deltaTime) {
		state += period;
		spawnParticle(state, deltaTime);
	}
	state -= deltaTime;
	oldWorldPos = currWorldPos;

}

Particle ParticleEmitter::makeParticle(float frameTimePassed, float deltaTime, vec3f position) {
	(void) frameTimePassed;
	(void) deltaTime;
	(void) position;
	return Particle();
}

void ParticleEmitter::spawnParticle(float frameTimePassed, float deltaTime) {
	float t2 = frameTimePassed/deltaTime;
	Particle pt = makeParticle(frameTimePassed, deltaTime, oldWorldPos * (1-t2) + currWorldPos * t2);
	pt.update(deltaTime-frameTimePassed); //update for the rest of the frame time
	sys->addParticle(pt);
}
