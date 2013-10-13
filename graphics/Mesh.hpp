#ifndef MESH_HPP
#define MESH_HPP
#include "Vertex.hpp"

class ShaderBinding;
class ShaderProgram;
class Mesh {
	public:
		enum PrimitiveType {
			TRIANGLES = GL_TRIANGLES,
			TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
			LINES = GL_LINES,
			LINE_STRIP = GL_LINE_STRIP,
			POINTS = GL_POINTS
		};

		enum BufferType {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW,
			STREAM = GL_STREAM_DRAW
		};

		Mesh(const Vertex::Format &vertexFormat, unsigned int vertexCount, BufferType dynamic = STATIC);
		Mesh(const std::string &filename, BufferType dynamic = STATIC);
		~Mesh();
		bool loadFromFile(const std::string &filename);

		void draw(const ShaderProgram* program);

		const Vertex::Format& getVertexFormat() const;
		unsigned int getVertexCount() const;
		unsigned int getVertexSize() const;
		BufferType getType() const;
		GLuint getVertexBuffer() const;

		PrimitiveType getPrimitiveType() const;
		void setPrimitiveType(Mesh::PrimitiveType type);
		void setVertexData(void* vertexData, unsigned int newVertexCount);

	private:
		void makeVBO();
		std::map<GLuint,const ShaderBinding*> bindingsCache;
		Vertex::Format vertexFormat;
		unsigned int vertexCount;
		GLuint vertexBuffer;
		PrimitiveType primitiveType;
		BufferType bufferType;
};

#endif // MESH_HPP
