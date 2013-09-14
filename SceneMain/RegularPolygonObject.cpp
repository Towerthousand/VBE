#include "RegularPolygonObject.hpp"
#include "../Game.hpp"

vec3f HuetoRGB(float h) {
	float r, g, b;
	h /= ( 2.0 * M_PI * (1.0 / 6.0) );
	int i = floor( h );
	float f = h - i;
	float q = 1 - 1 * f;
	float t = 1 - 1 * ( 1 - f );

	switch( i ) {
		case 0: r = 1; g = t; b = 0; break;
		case 1: r = q; g = 1; b = 0; break;
		case 2: r = 0; g = 1; b = t; break;
		case 3: r = 0; g = q; b = 1; break;
		case 4: r = t; g = 0; b = 1; break;
		case 5: default:
			r = 1; g = 0; b = q; break;
	}

	return vec3f(r,g,b);
}

RegularPolygonObject::RegularPolygonObject(Scene* parentScene, const vec3f &pos, const vec3f &scale, unsigned int sides) : GameObject(parentScene, pos, scale) {
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Color    , Vertex::Element::Float, 3));

	Vertex::Format format(elements);
	Mesh* mesh = new Mesh(format,0,false);

	struct Vertex {
			Vertex(vec3f pos, vec3f color) : pos(pos) , color(color) {}
			vec3f pos, color;
	};

	float angle = 0;
	float angleStep = 2.0 * M_PI * (1.0f/sides);
	std::vector<Vertex> data;
	for (unsigned int i = 0; i < sides; ++i) {
		data.push_back(Vertex(vec3f(0.0, 0.0, 0.0), vec3f(1.0, 1.0, 1.0)));
		data.push_back(Vertex(vec3f(std::cos(angle), std::sin(angle),0.0), HuetoRGB(angle))); angle += angleStep;
		data.push_back(Vertex(vec3f(std::cos(angle), std::sin(angle),0.0), HuetoRGB(angle)));
	}

	mesh->setVertexData(&data[0],data.size());
	poly.mesh = mesh;
	poly.program = ShaderManager::get("sample2");
}

RegularPolygonObject::~RegularPolygonObject() {
}

void RegularPolygonObject::update(float deltaTime) {
	(void) deltaTime;
	updateMatrix();
}

void RegularPolygonObject::updateMatrix() {
	mat4f m(1.0);
	m = glm::translate(m,pos);
	m = glm::rotate(m,GLOBALCLOCK.getElapsedTime().asSeconds()*50,vec3f(0,0,1));
	m = glm::scale(m,scale);
	poly.modelMatrix = m;
}

void RegularPolygonObject::draw() const {
	mat4f transform = parentScene->getState().projection*parentScene->getState().view*poly.modelMatrix;
	poly.program->uniform("modelViewProjectionMatrix")->set(transform);
	poly.draw();
}
