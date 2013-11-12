#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "Particle.hpp"

class ParticleSystem : public GameObject {
	public:
		ParticleSystem();
		~ParticleSystem();
		void update(float deltaTime);
		void draw() const;
		void addParticle(const Particle& p);
		int getParticleCount() const { return particles.size(); }
		void setTextureSheet(Texture* textureSheet, unsigned int textureCount);
		void setProjectionMatrix(const mat4f& mat) {projectionMatrix = mat;}
		void setViewMatrix(const mat4f& mat) {viewMatrix = mat;}

	private:
		static const std::string vertexShader;
		static const std::string geometryShader;
		static const std::string fragmentShader;

		std::list<Particle> particles;
		Model model;
		unsigned int textureCount;
		Texture* textureSheet;
		mat4f projectionMatrix;
		mat4f viewMatrix;
};

#endif // PARTICLESYSTEM_HPP
