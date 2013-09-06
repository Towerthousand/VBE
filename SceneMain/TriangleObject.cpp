#include "TriangleObject.hpp"
#include "SceneMain.hpp"
#include "../Game.hpp"

TriangleObject::TriangleObject(SceneMain* parentScene, vec3f pos, vec3f scale) : GameObject(parentScene,pos,scale) {
	//NEW WAY
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Color    , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));

	Vertex::Format format(elements);
	Mesh* mesh = new Mesh(format,0,false);

	struct Vertex {
			Vertex(vec3f pos, vec3f color) : pos(pos) , color(color) {}
			vec3f color,pos;
	};
	std::vector<Vertex> data;
	data.push_back(Vertex(vec3f(-1.0, -0.577,  0.0), vec3f(0.0, 0.0, 1.0)));
	data.push_back(Vertex(vec3f( 1.0, -0.577,  0.0), vec3f(0.0, 1.0, 0.0)));
	data.push_back(Vertex(vec3f( 0.0,  1.155,  0.0), vec3f(1.0, 0.0, 0.0)));

	mesh->setVertexData(&data[0],data.size());
	this->tri.mesh = mesh;
	this->tri.program = parentScene->shaderExample;
}

TriangleObject::~TriangleObject() {

}

void TriangleObject::update(float deltaTime) {
	updateMatrix();
}

void TriangleObject::updateMatrix() {
	mat4f m(1.0);
	m = glm::translate(m,vec3f(0,0,-2));
	m = glm::rotate(m,GLOBALCLOCK.getElapsedTime().asSeconds()*50,vec3f(0,0,1));
	m = glm::scale(m,scale);
	tri.modelMatrix = m;
}

void TriangleObject::draw() const {
	mat4f transform = parentScene->getState().projection*parentScene->getState().view*tri.modelMatrix;
	tri.program->uniform("modelViewProjectionMatrix")->set(transform);
	tri.draw();
}
