#ifndef MESHINDEXED_HPP
#define MESHINDEXED_HPP

#include <VBE/graphics/MeshBase.hpp>

class MeshIndexed final : public MeshBase {
	public:
		MeshIndexed(const Vertex::Format& format, MeshBase::BufferType bufferType = STATIC);
		~MeshIndexed() override;
		MeshIndexed(MeshIndexed&& rhs);
		MeshIndexed& operator=(MeshIndexed&& rhs);

		void bindBuffers() const override;

		void draw(const ShaderProgram* program) override;
		GLuint getIndexBuffer() const;
		unsigned int getIndexCount() const;
		void setIndexData(const unsigned int* indexData, unsigned int newIndexCount);

		friend void swap(MeshIndexed& a, MeshIndexed& b);

	private:
		unsigned int indexCount;
		GLuint indexBuffer;
};


#endif // MESHINDEXED_HPP
