#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "../../includes.hpp"

class Particle {
	public:
		struct Vertex {
				vec3f pos;
				vec3f vel;
				vec4f col;
				float size;
				int texIndex;
		};
		Particle();
		bool isAlive() {return (lifeLeft>0);}
		void update(float deltaTime);
		void render(Particle::Vertex& vtx) const;

		float life; //Tiempo de vida en segundos. No cambia
		float lifeLeft; //Tiempo que queda de vida. 1..0
		float startSize, endSize;
		vec4f startCol, endCol;
		vec3f p, v, a;
		int texIndex;

	private:
		friend class ParticleEmitter;
};

#endif //PARTICLE_HPP
