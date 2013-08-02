#include "TriangleObject.hpp"
#include "../Game.hpp"
TriangleObject::TriangleObject(SceneMain* parentScene, vec3f pos, vec3f scale) : GameObject(parentScene,pos,scale),
	vertexCount(0), VBOHANDLE(0) {

	std::vector<Vertex> renderData;
	//VERTEX FORMAT:             X     Y       Z      R    G    B    A
	renderData.push_back(Vertex(-1.0, -0.577,  0.0,   0  , 0  , 1.0, 1.0));
	renderData.push_back(Vertex( 1.0, -0.577,  0.0,   0  , 1.0, 0  , 1.0));
	renderData.push_back(Vertex( 0.0,  1.155,  0.0,   1.0, 0  , 0  , 1.0));

	renderData.push_back(Vertex( 1.0, -0.577,  0.0,   0  , 1.0,   0, 1.0));
	renderData.push_back(Vertex(-1.0, -0.577,  0.0,   0  , 0  , 1.0, 1.0));
	renderData.push_back(Vertex( 0.0,  1.155,  0.0,   1.0, 0  ,   0, 1.0));

	vertexCount = renderData.size();

	glGenBuffers(1, (GLuint*) &VBOHANDLE);
	glBindBuffer(GL_ARRAY_BUFFER, VBOHANDLE);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(Vertex), &renderData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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
	parentScene->getShader("SHADER").use();
	parentScene->getState().updateShaderUniforms(parentScene->getShader("SHADER"));

	glBindBuffer(GL_ARRAY_BUFFER, VBOHANDLE);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3*sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	parentScene->getState().model = poppedMat;
}
