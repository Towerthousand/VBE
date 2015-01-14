#ifndef MESHSEPARATE_HPP
#define MESHSEPARATE_HPP
#include <VBE/graphics/MeshBase.hpp>

class ShaderBinding;
class ShaderProgram;
class MeshSeparate : public MeshBase {
	public:
		MeshSeparate();
		MeshSeparate(const Vertex::Format& format, BufferType bufferType = STATIC);
		virtual ~MeshSeparate() override;

		void setVertexData(const void* vertexData, unsigned int newVertexCount) override final;
		virtual void bindBuffers() const;
		GLuint getVertexBuffer() const;

		friend void swap(MeshSeparate& a, MeshSeparate& b);
	protected:
		void setupShaderBinding(const ShaderProgram& program);

	private:
		std::map<GLuint, const ShaderBinding*> bindingsCache;
		GLuint vertexBuffer = 0;
};

#endif // MESHSEPARATE_HPP
