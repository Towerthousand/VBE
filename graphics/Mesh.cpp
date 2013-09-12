#include "Mesh.hpp"
#include "ShaderProgram.hpp"

Mesh::Mesh(const Vertex::Format& vertexFormat, unsigned int vertexCount, bool dynamic)
	: vertexFormat(vertexFormat), vertexCount(vertexCount), vertexBuffer(0), primitiveType(TRIANGLES),
	  dynamic(dynamic) {
	makeVBO();
}

Mesh::Mesh(const std::string &filename, bool dynamic)
	: vertexFormat(std::vector<Vertex::Element>()), vertexCount(0), vertexBuffer(0), primitiveType(TRIANGLES),
	  dynamic(dynamic){
	if (!loadFromFile(filename)) {
		std::cout << "Could not load mesh from " << filename <<
					 ". VBO will not be generated for this mesh" << std::endl;
		return;
	}
}

Mesh::~Mesh() {
	if(vertexBuffer != 0) {
		glDeleteBuffers(1,&vertexBuffer);
	}
	for(std::map<GLuint,const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it) {
		delete it->second;
	}
}

bool Mesh::loadFromFile(const std::string& filename) {
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Normal   , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

	struct vert {
			vert(vec3f pos, vec3f normal, vec2f tex) : pos(pos) , normal(normal), tex(tex) {}
			vec3f pos,normal;
			vec2f tex;
	};

	std::ifstream in(filename.c_str(), std::ifstream::in);
	if (!in) {
		std::cout << "Cannot open " << filename << std::endl;
		return false;
	}

	std::vector<vec3f> vertices;
	std::vector<vec3f> normals;
	std::vector<vec2f> textures;
	std::vector<vert> data;

	std::string line;
	while (getline(in, line)) {
		if (line.substr(0,2) == "v ") {
			std::istringstream s(line.substr(2));
			vec3f v;
			s >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		else if (line.substr(0,3) == "vn ") {
			std::istringstream s(line.substr(3));
			vec3f v;
			s >> v.x >> v.y >> v.z;
			normals.push_back(v);
		}
		else if (line.substr(0,3) == "vt ") {
			std::istringstream s(line.substr(3));
			vec2f v;
			s >> v.x >> v.y;
			v.y = 1-v.y;
			textures.push_back(v);
		}
		else if (line.substr(0,2) == "f ") {
			std::istringstream s(line.substr(2));
			int v1, v2, v3, n1, n2, n3, t1, t2, t3;
			char b;
			s >> v1 >> b >> t1 >> b >> n1
			  >> v2 >> b >> t2 >> b >> n2
			  >> v3 >> b >> t3 >> b >> n3;
			data.push_back(vert(vertices[v1-1],normals[n1-1],textures[t1-1]));
			data.push_back(vert(vertices[v2-1],normals[n2-1],textures[t2-1]));
			data.push_back(vert(vertices[v3-1],normals[n3-1],textures[t3-1]));
		}
	}

	makeVBO();
	vertexFormat = Vertex::Format(elements);
	setVertexData(&data[0],data.size());
	return true;
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

void Mesh::makeVBO() {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	if (glGetError()){
		std::cout << "Failed to create VBO for mesh" << std::endl;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (glGetError()) {
		std::cout << "Failed to bind VBO for mesh" << std::endl;
		glDeleteBuffers(1, &vbo);
		return;
	}

	glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, NULL, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	if (glGetError()) {
		std::cout << "Failed to load VBO with empty vertex data" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vbo);
		return;
	}

	vertexBuffer = vbo;
}
