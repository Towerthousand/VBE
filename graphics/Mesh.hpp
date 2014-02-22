#ifndef MESH_HPP
#define MESH_HPP

#include "Vertex.hpp"
#include "geometry/AABB.hpp"

class ShaderBinding;
class ShaderProgram;
class Mesh {
	public:
		enum PrimitiveType {
			TRIANGLES = GL_TRIANGLES,
			TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
			LINES = GL_LINES,
			LINE_STRIP = GL_LINE_STRIP,
			POINTS = GL_POINTS,
			PATCHES = GL_PATCHES
		};

		enum BufferType {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW,
			STREAM = GL_STREAM_DRAW
		};

		static Mesh* loadFromFile(const std::string filepath, Mesh::BufferType bufferType = STATIC);
		static Mesh* loadEmpty(Vertex::Format format, Mesh::BufferType bufferType = STATIC, bool indexed = false);

		~Mesh();

		void draw(const ShaderProgram* program);

		const Vertex::Format& getVertexFormat() const;
		unsigned int getVertexCount() const;
		unsigned int getVertexSize() const;
		BufferType getType() const;
		GLuint getVertexBuffer() const;
		GLuint getIndexBuffer() const;
		PrimitiveType getPrimitiveType() const;
		bool isIndexed() const;

        AABB getBoundingBox() const;

		void setPrimitiveType(Mesh::PrimitiveType type);
		void setVertexData(void* vertexData, unsigned int newVertexCount);
		void setVertexIndices(unsigned int* indexData, unsigned int newIndexCount);

	private:
		Mesh(Vertex::Format format, BufferType bufferType = STATIC, bool indexed = false);

		std::map<GLuint, const ShaderBinding*> bindingsCache;
		const Vertex::Format vertexFormat;
		unsigned int vertexCount;
		unsigned int indexCount;
		GLuint vertexBuffer;
		GLuint indexBuffer;
		PrimitiveType primitiveType;
		BufferType bufferType;
		bool indexed;

        AABB aabb;
		friend class OBJLoader;
};

#endif // MESH_HPP
