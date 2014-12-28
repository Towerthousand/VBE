#ifndef MESHSEPARATE_HPP
#define MESHSEPARATE_HPP
#include <VBE/graphics/MeshBase.hpp>

class ShaderBinding;
class ShaderProgram;
class MeshSeparate : public MeshBase {
	public:
		MeshSeparate(const Vertex::Format& format, BufferType bufferType = STATIC);
		virtual ~MeshSeparate() override;

		virtual void draw(const ShaderProgram* program) override = 0;
		void setVertexData(const void* vertexData, unsigned int newVertexCount) override final;
		virtual void bindBuffers() const;
		GLuint getVertexBuffer() const;

		friend void swap(MeshSeparate& a, MeshSeparate& b);
	protected:
		void setupShaderBinding(const ShaderProgram* program);

	private:
		std::map<GLuint, const ShaderBinding*> bindingsCache;
		GLuint vertexBuffer;
};

#endif // MESHSEPARATE_HPP
