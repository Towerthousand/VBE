#include "TriangleObject.hpp"
#include "../Game.hpp"

TriangleObject::TriangleObject(SceneMain* parentScene, vec3f pos, vec3f scale) : GameObject(parentScene,pos,scale) {
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

	mesh->setVertexData(&data[0],data.size());
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
	//ideally, this would be something like:
	//Effect::useEffect("SHADER"); //binds the effect

	//Effect::uniform("modelviewProjectionMatrix").set(transformMatrixAsMat4f);

	//Effect::ready();             //sends all the uniforms from the renderstate
	//							   //to the program if they exist and have changed, updates all the
	//						       //openGL variables to match the renderstate.

	//tri.draw();				   //creates a vertexBinding for this efffect if one didn't exist
	//							   //with this mesh's vertexFormat. Once it has a binding, it uses it
	//							   //to set the model-associated uniforms that exist in the shader and
	//							   //have changed. Then it binds the vertex attributes that match
	//							   //between the program and the vertex format, and draws.

	//Effect::releaseEffect();	   //unbinds effect

	//Now it is done by hand
	mat4f poppedMat = parentScene->getState().model;
	parentScene->getState().model = modelMatrix;
	mat4f transform = parentScene->getState().projection*parentScene->getState().view*parentScene->getState().model;

	ShaderProgram::get("SHADER")->bind();
	GLint location = glGetUniformLocation(3, (GLchar *)std::string("modelViewProjectionMatrix").c_str()); //dat 3 hardcoded
	glUniformMatrix4fv(location, 1, GL_FALSE, &transform[0][0]);
	tri.draw();

	parentScene->getState().model = poppedMat;
}
