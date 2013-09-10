#include "TriangleObject.hpp"
#include "SceneMain.hpp"
#include "../Game.hpp"

TriangleObject::TriangleObject(Scene* parentScene, ShaderProgram *program, vec3f pos, vec3f scale) : GameObject(parentScene,pos,scale) {
	std::vector<Vertex::Element> elements;
    elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Color    , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

	Vertex::Format format(elements);
	Mesh* mesh = new Mesh(format,0,false);

	struct Vertex {
			Vertex(vec3f pos, vec3f color, vec2f tex) : pos(pos) , color(color), tex(tex) {}
			vec3f pos,color;
			vec2f tex;
	};

	std::vector<Vertex> data;
	data.push_back(Vertex(vec3f(-1.0, -1.0,  0.0), vec3f(0.0, 0.0, 1.0), vec2f(0.0,10.0)));
	data.push_back(Vertex(vec3f( 1.0, -1.0,  0.0), vec3f(0.0, 1.0, 0.0), vec2f(10.0,10.0)));
	data.push_back(Vertex(vec3f(-1.0,  1.0,  0.0), vec3f(1.0, 0.0, 0.0), vec2f(0.0,0.0)));

	data.push_back(Vertex(vec3f( 1.0, -1.0,  0.0), vec3f(0.0, 0.0, 1.0), vec2f(10.0,10.0)));
	data.push_back(Vertex(vec3f( 1.0,  1.0,  0.0), vec3f(0.0, 1.0, 0.0), vec2f(10.0,0.0)));
	data.push_back(Vertex(vec3f(-1.0,  1.0,  0.0), vec3f(1.0, 0.0, 0.0), vec2f(0.0,0.0)));

	mesh->setVertexData(&data[0],data.size());
	tri.mesh = mesh;
	tri.program = program;
}

TriangleObject::~TriangleObject() {
	delete tri.mesh;
}

void TriangleObject::update(float deltaTime) {
    (void) deltaTime;
	updateMatrix();
}

void TriangleObject::updateMatrix() {
	mat4f m(1.0);
	m = glm::translate(m,pos);
	m = glm::rotate(m,GLOBALCLOCK.getElapsedTime().asSeconds()*50,vec3f(0,0,1));
	m = glm::scale(m,scale);
	tri.modelMatrix = m;
}

void TriangleObject::draw() const {
	mat4f transform = parentScene->getState().projection*parentScene->getState().view*tri.modelMatrix;
	TextureManager::useTexture("textest",  GL_TEXTURE2);
	tri.program->uniform("sampler")->set(2);
	tri.program->uniform("modelViewProjectionMatrix")->set(transform);
	tri.draw();
}
