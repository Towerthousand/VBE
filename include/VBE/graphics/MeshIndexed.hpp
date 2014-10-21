#ifndef MESHINDEXED_HPP
#define MESHINDEXED_HPP

#include <VBE/graphics/MeshBase.hpp>

class MeshIndexed : public MeshBase {
	public:
		MeshIndexed(const Vertex::Format& format, MeshBase::BufferType bufferType = STATIC);
		~MeshIndexed() override;

		void bindBuffers() const override;

		void draw(const ShaderProgram* program) override;
		GLuint getIndexBuffer() const;
		unsigned int getIndexCount() const;
		void setIndexData(const unsigned int* indexData, unsigned int newIndexCount);

	private:
		unsigned int indexCount;
		GLuint indexBuffer;
};


#endif // MESHINDEXED_HPP
