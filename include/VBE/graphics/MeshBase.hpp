#ifndef MESHBASE_HPP
#define MESHBASE_HPP
#include <VBE/graphics/MeshInterface.hpp>

class ShaderBinding;
class ShaderProgram;
class MeshBase : public MeshInterface {
	public:
		MeshBase(const Vertex::Format& format, MeshBase::BufferType bufferType = STATIC);
		virtual ~MeshBase() override;
		MeshBase(MeshBase&& rhs);
		MeshBase& operator=(MeshBase&& rhs);

		virtual void draw(const ShaderProgram* program) override = 0;
		void setVertexData(const void* vertexData, unsigned int newVertexCount) override final;
		virtual void bindBuffers() const;
		GLuint getVertexBuffer() const;

		friend void swap(MeshBase& a, MeshBase& b);
	protected:
		void setupShaderBinding(const ShaderProgram* program);

	private:
		std::map<GLuint, const ShaderBinding*> bindingsCache;
		GLuint vertexBuffer;
};

#endif // MESHBASE_HPP
