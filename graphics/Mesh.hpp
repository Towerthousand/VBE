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

		Mesh(BufferType bufferType = STATIC, bool indexed = false);
		~Mesh();
		void loadFromFile(const std::string &filename);

		void draw(const ShaderProgram* program);

		const Vertex::Format& getVertexFormat() const;
		unsigned int getVertexCount() const;
		unsigned int getVertexSize() const;
		BufferType getType() const;
		GLuint getVertexBuffer() const;
		GLuint getIndexBuffer() const;
		PrimitiveType getPrimitiveType() const;
		bool isIndexed() const;

		void setVertexFormat(const Vertex::Format& format);
		void setPrimitiveType(Mesh::PrimitiveType type);
		void setVertexData(void* vertexData, unsigned int newVertexCount);
		void setVertexIndices(unsigned short* indexData, unsigned int newIndexCount);

	private:
		std::map<GLuint,const ShaderBinding*> bindingsCache;
		Vertex::Format vertexFormat;
		unsigned int vertexCount;
		unsigned int indexCount;
		GLuint vertexBuffer;
		GLuint indexBuffer;
		PrimitiveType primitiveType;
		BufferType bufferType;
		bool indexed;
};

#endif // MESH_HPP
