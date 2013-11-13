#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem() :
	textureCount(0), textureSheet(nullptr),
	projectionMatrix(1.0f), viewMatrix(1.0f) {
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position   , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::get("a_vel"), Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Color      , Vertex::Element::Float, 4));
	elements.push_back(Vertex::Element(Vertex::Attribute::get("a_size"), Vertex::Element::Float, 1));
	elements.push_back(Vertex::Element(Vertex::Attribute::get("a_texIndex"), Vertex::Element::Int, 1));

	model.mesh = Mesh::loadEmpty(Vertex::Format(elements),Mesh::STREAM);
	model.mesh->setPrimitiveType(Mesh::POINTS);
	model.program = ShaderProgram::loadFromString(vertexShader,geometryShader,fragmentShader);
	setName("particleSystem");
	setUpdatePriority(-100);
	setDrawPriority(100);
}

ParticleSystem::~ParticleSystem() {
	delete model.mesh;
	delete model.program;
}

void ParticleSystem::update(float deltaTime) {
	for(std::list<Particle>::iterator it = particles.begin(); it != particles.end();) {
		it->update(deltaTime);
		if(!it->isAlive())
			it = particles.erase(it);
		else
			++it;
	}
	std::vector<Particle::Vertex> vtxs;
	vtxs.resize(particles.size());
	int i = 0;
	for(std::list<Particle>::const_iterator it = particles.begin(); it != particles.end(); it++) {
		it->render(vtxs[i]);
		i++;
	}
	model.mesh->setVertexData(&vtxs[0], particles.size());
}

void ParticleSystem::draw() const {
	if(particles.size() == 0)
		return;
	VBE_ASSERT(textureSheet != nullptr, "Cannot draw textureless particles, give particleSystem a textureSheet before emitting particles");
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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

const std::string ParticleSystem::vertexShader (
		" \
		#version 420 core\n\
			\
			uniform mat4 modelViewMatrix; \
			in vec3 a_position; \
			in vec3 a_vel; \
			in vec4 a_color; \
			in float a_size; \
			in int a_texIndex; \
			out vec2 geom_vel; \
			out vec4 geom_color; \
			out float geom_size; \
			out int geom_texIndex; \
			void main () { \
			gl_Position = modelViewMatrix * vec4(a_position, 1.0); \
			geom_color = a_color; \
			geom_size = a_size; \
			geom_texIndex = a_texIndex; \
			geom_vel = vec3(mat3(modelViewMatrix)*a_vel).xy; \
			}"
		);

const std::string ParticleSystem::geometryShader (
		" \
		#version 420 core//4.2\n\
		\
		layout (points) in; \
layout (triangle_strip, max_vertices = 4) out; \
\
uniform mat4 projectionMatrix; \
uniform mat4 modelViewMatrix; \
uniform float texSize; // 1.0 / num de texturas \n\
\
in vec2 geom_vel[]; \
in vec4 geom_color[]; \
in float geom_size[]; \
in int geom_texIndex[]; \
\
out vec2 v_texCoord; \
out vec4 v_color; \
\
const vec2[4] texCoords = { \
	vec2( 1, 1), \
	vec2( 0, 1), \
	vec2( 1, 0), \
	vec2( 0, 0) \
}; \
\
const vec2[4] displacements = { \
	vec2( 1, 1), \
	vec2(-1, 1), \
	vec2( 1,-1), \
	vec2(-1,-1) \
}; \
\
void main() { \
	vec3 front = normalize(gl_in[0].gl_Position.xyz); \
	vec3 vel = vec3(geom_vel[0],0.0f); \
	vec3 up = cross(front,vel); \
	\
	mat3 transform = mat3(1.0); \
	\
	if(length(up) < 0.0001) { \
		up = vec3(0.0, 1.0, 0.0); \
		vec3 right = normalize(cross(front,up)); \
		up = cross(front, right); \
		transform = mat3(right,up,front); \
	} \
	else { \
		up = normalize(up); \
		vec3 right = normalize(cross(front,up)); \
		float len = length(vel); \
		transform = mat3(right*(1+len*0.2),up,front); \
	} \
	\
	for(int i = 0; i < 4; i++) { \
		// copy attributes \n\
		vec3 disp = transform*vec3(displacements[i], 0.0); \
		gl_Position = projectionMatrix * (gl_in[0].gl_Position + vec4(disp * geom_size[0], 0.0)); \
		v_texCoord.x = texSize*(float(geom_texIndex[0]) + float(texCoords[i].x)); \
		v_texCoord.y = texCoords[i].y; \
		v_color = geom_color[0]; \
		// done with the vertex  \n\
		EmitVertex(); \
	} \
	EndPrimitive(); \
}"
);

const std::string ParticleSystem::fragmentShader (
		" \
		#version 420 core //4.2\n\
		uniform sampler2D textureSheet; \
in vec2 v_texCoord; \
in vec4 v_color; \
void main() { \
	gl_FragColor = v_color*texture(textureSheet,v_texCoord); \
}"
);
