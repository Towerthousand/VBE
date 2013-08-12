#include "TriangleObject.hpp"
#include "../Game.hpp"

TriangleObject::TriangleObject(SceneMain* parentScene, vec3f pos, vec3f scale) : GameObject(parentScene,pos,scale),
	vertexCount(0), VBOHANDLE(0) {
	//NEW WAY
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Color    , Vertex::Element::Float, 3));

	Vertex::Format format(elements);
	Mesh* mesh = new Mesh(format,0,false);

	struct Vertex {
			Vertex(vec3f pos, vec3f color) : pos(pos) , color(color) {}
			vec3f pos,color;
	};
	std::vector<Vertex> data;
	data.push_back(Vertex(vec3f(-1.0, -0.577,  0.0), vec3f(0.0, 0.0, 1.0)));
	data.push_back(Vertex(vec3f( 1.0, -0.577,  0.0), vec3f(0.0, 1.0, 0.0)));
	data.push_back(Vertex(vec3f( 0.0,  1.155,  0.0), vec3f(1.0, 0.0, 0.0)));

	mesh->setVertexData(&data[0],3);
	this->tri.setMesh(mesh);
}

TriangleObject::~TriangleObject() {

}

void TriangleObject::update(float deltaTime) {
	updateMatrix();
}

void TriangleObject::updateMatrix() {
	modelMatrix = mat4f(1.0);
	modelMatrix = glm::translate(modelMatrix,vec3f(0,0,-2));
	modelMatrix = glm::rotate(modelMatrix,GLOBALCLOCK.getElapsedTime().asSeconds()*100,vec3f(0,0,1));
	modelMatrix = glm::scale(modelMatrix,scale);
}

void TriangleObject::draw() const {
	mat4f poppedMat = parentScene->getState().model;
	parentScene->getState().model = modelMatrix;
	parentScene->getShader("SHADER").bind();
	parentScene->getState().updateShaderUniforms(parentScene->getShader("SHADER"));

	tri.draw();

	parentScene->getState().model = poppedMat;
}
