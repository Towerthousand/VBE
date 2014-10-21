#ifndef MESHBASE_HPP
#define MESHBASE_HPP

#include <map>
#include <string>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Vertex.hpp>
#include <VBE/utils/NonCopyable.hpp>

class ShaderBinding;
class ShaderProgram;
class MeshBase : public NonCopyable {
	public:
		enum PrimitiveType {
			TRIANGLES = GL_TRIANGLES,
			TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
			TRIANGLE_FAN = GL_TRIANGLE_FAN,
			LINES = GL_LINES,
			LINE_STRIP = GL_LINE_STRIP,
			LINE_LOOP = GL_LINE_LOOP,
			POINTS = GL_POINTS,
#ifndef VBE_GLES2
			PATCHES = GL_PATCHES
#endif
		};

		enum BufferType {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW,
			STREAM = GL_STREAM_DRAW
		};

		virtual ~MeshBase();

		virtual void draw(const ShaderProgram* program) = 0;

		const Vertex::Format& getVertexFormat() const;
		unsigned int getVertexCount() const;
		unsigned int getVertexSize() const;
		GLuint getVertexBuffer() const;
		PrimitiveType getPrimitiveType() const;
		BufferType getBufferType() const;

		void setPrimitiveType(MeshBase::PrimitiveType type);
		void setVertexData(const void* vertexData, unsigned int newVertexCount);

		virtual void bindBuffers() const;

		friend void swap(MeshBase& a, MeshBase& b);
	protected:
		MeshBase(const Vertex::Format& format, MeshBase::BufferType bufferType = STATIC);
		void setupShaderBinding(const ShaderProgram* program);

	private:
		std::map<GLuint, const ShaderBinding*> bindingsCache;
		Vertex::Format vertexFormat;
		unsigned int vertexCount;
		GLuint vertexBuffer;
		PrimitiveType primitiveType;
		BufferType bufferType;
};

#endif // MESHBASE_HPP
