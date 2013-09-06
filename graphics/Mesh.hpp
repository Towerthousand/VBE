#ifndef MESH_HPP
#define MESH_HPP
#include "Vertex.hpp"
#include "ShaderBinding.hpp"

class Mesh {
	public:
		enum PrimitiveType {
			TRIANGLES = GL_TRIANGLES,
			TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
			LINES = GL_LINES,
			LINE_STRIP = GL_LINE_STRIP,
			POINTS = GL_POINTS
		};

		Mesh(const Vertex::Format& vertexFormat, unsigned int vertexCount, bool dynamic = false);
		~Mesh();

		void draw(ShaderProgram* program);

		const Vertex::Format& getVertexFormat() const;
		unsigned int getVertexCount() const;
		unsigned int getVertexSize() const;
		bool isDynamic() const;
		GLuint getVertexBuffer() const;

		PrimitiveType getPrimitiveType() const;
		void setPrimitiveType(Mesh::PrimitiveType type);
		void setVertexData(void* vertexData, unsigned int newVertexCount);

	protected:
		std::map<GLuint,const ShaderBinding*> bindingsCache;
		const Vertex::Format vertexFormat;
		unsigned int vertexCount;
		GLuint vertexBuffer;
		PrimitiveType primitiveType;
		bool dynamic;
};

#endif // MESH_HPP
