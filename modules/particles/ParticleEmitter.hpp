#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include "Particle.hpp"

class ParticleSystem;
class ParticleEmitter : public GameObject {
	public:
		ParticleEmitter(int particlesPerSecond);
		virtual ~ParticleEmitter();

		virtual void update(float deltaTime);

		int getParticlesPerSecond() {return floor(1.0f/period);}
		void setParticlesPerSecond(int particlesPerSecond) {period = 1.0f/particlesPerSecond;}

	protected:
		virtual Particle makeParticle(float frameTimePassed, float deltaTime, vec3f position);
		vec3f oldWorldPos;
		vec3f currWorldPos;
	private:
		void spawnParticle(float frameTimePassed, float deltaTime);

		float period;
		ParticleSystem* sys;
		float state;
};

#endif // PARTICLEEMITTER_HPP
