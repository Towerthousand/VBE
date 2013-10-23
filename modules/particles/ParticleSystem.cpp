#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem() :
	textureCount(0), textureSheet(NULL),
	projectionMatrix(1.0f), viewMatrix(1.0f) {
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position   , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::get("a_vel"), Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Color      , Vertex::Element::Float, 4));
	elements.push_back(Vertex::Element(Vertex::Attribute::get("a_size"), Vertex::Element::Float, 1));
	elements.push_back(Vertex::Element(Vertex::Attribute::get("a_texIndex"), Vertex::Element::Int, 1));
	Vertex::Format format(elements);

	Mesh* mesh= new Mesh(format, 0, Mesh::STREAM);
	mesh->setPrimitiveType(Mesh::POINTS);
	model.mesh = mesh;
	Meshes.add("particlesMesh",mesh);
	model.program = Programs.get("particleShader");
	setName("particleSystem");
	setUpdatePriority(-100);
	setDrawPriority(100);
}

void ParticleSystem::update(float deltaTime) {
	for(std::list<Particle>::iterator it = particles.begin(); it != particles.end();) {
		it->update(deltaTime);
		if(!it->isAlive())
			it = particles.erase(it);
		else
			++it;
	}
}

void ParticleSystem::draw() const {
	if(particles.size() == 0)
		return;
	VBE_ASSERT(textureSheet != NULL, "Cannot draw textureless particles, give particleSystem a textureSheet before emitting particles");
	if(vtxs.size() < particles.size())
		vtxs.resize(particles.size());

	int i = 0;
	for(std::list<Particle>::const_iterator it = particles.begin(); it != particles.end(); it++) {
		it->render(vtxs[i]);
		i++;
	}
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	model.mesh->setVertexData(&vtxs[0], particles.size());
	model.program->uniform("modelViewMatrix")->set(viewMatrix*fullTransform);
	model.program->uniform("projectionMatrix")->set(projectionMatrix);
	model.program->uniform("texSize")->set(1.0f/float(textureCount));
	model.program->uniform("textureSheet")->set(textureSheet);
	model.draw();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
}

void ParticleSystem::addParticle(const Particle& p) {
	particles.push_back(p);
}

void ParticleSystem::setTextureSheet(Texture* textureSheet, unsigned int textureCount) {
	this->textureSheet = textureSheet;
	this->textureCount = textureCount;
}

