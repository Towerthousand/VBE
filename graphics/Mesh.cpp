#include "Mesh.hpp"
#include "ShaderProgram.hpp"

Mesh::Mesh(const Vertex::Format& vertexFormat, unsigned int vertexCount, bool dynamic)
	: vertexFormat(vertexFormat), vertexCount(vertexCount), vertexBuffer(0), primitiveType(TRIANGLES),
	  dynamic(dynamic) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	if (glGetError()){
		std::cout << "Failed to create VBO for mesh" << std::endl;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (glGetError()) {
		std::cout << "Failed to bind VBO for mesh" << std::endl;
		glDeleteBuffers(1, &vbo);
	}

	glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, NULL, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	if (glGetError()) {
		std::cout << "Failed to load VBO with vertex data" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vbo);
		return;
	}
	vertexBuffer = vbo;
}

Mesh::~Mesh() {
	if(vertexBuffer != 0) {
		glDeleteBuffers(1,&vertexBuffer);
	}
}

void Mesh::draw(ShaderProgram* program) {
	GLuint handle = program->getHandle();
	if(bindingsCache.find(handle) == bindingsCache.end()) {
		bindingsCache.insert(std::pair<GLuint,const ShaderBinding*>(handle,new ShaderBinding(program, this)));
	}
	const ShaderBinding* binding = bindingsCache.at(handle);
	program->use();
	binding->bindVAO();
	glDrawArrays(primitiveType, 0, vertexCount);
	binding->unbindVAO();
}

const Vertex::Format& Mesh::getVertexFormat() const {
	return vertexFormat;
}

unsigned int Mesh::getVertexCount() const {
	return vertexCount;
}

unsigned int Mesh::getVertexSize() const {
	return vertexFormat.vertexSize();
}

bool Mesh::isDynamic() const {
	return dynamic;
}

GLuint Mesh::getVertexBuffer() const {
	return vertexBuffer;
}

Mesh::PrimitiveType Mesh::getPrimitiveType() const {
	return primitiveType;
}

void Mesh::setPrimitiveType(Mesh::PrimitiveType type) {
	primitiveType = type;
}

void Mesh::setVertexData(void* vertexData, unsigned int newVertexCount) {
	vertexCount = newVertexCount;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, vertexData, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
