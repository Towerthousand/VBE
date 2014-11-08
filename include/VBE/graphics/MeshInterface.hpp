#ifndef MESHINTERFACE_HPP
#define MESHINTERFACE_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Vertex.hpp>
#include <VBE/utils/NonCopyable.hpp>

class ShaderBinding;
class ShaderProgram;
class MeshInterface : public NonCopyable {
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

		MeshInterface(const Vertex::Format& format, BufferType bufferType = STATIC);
		virtual ~MeshInterface();

		virtual void draw(const ShaderProgram* program) = 0;

		const Vertex::Format& getVertexFormat() const;
		unsigned int getVertexCount() const;
		unsigned int getVertexSize() const;
		PrimitiveType getPrimitiveType() const;
		BufferType getBufferType() const;

		void setPrimitiveType(PrimitiveType type);
		virtual void setVertexData(const void* vertexData, unsigned int newVertexCount) = 0;

		friend void swap(MeshInterface& a, MeshInterface& b);
	protected:
		unsigned int vertexCount;
	private:
		Vertex::Format vertexFormat;
		PrimitiveType primitiveType;
		BufferType bufferType;
};

#endif // MESHINTERFACE_HPP
