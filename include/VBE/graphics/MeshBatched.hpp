#ifndef MESHBATCHED_HPP
#define MESHBATCHED_HPP
#include <VBE/graphics/MeshBase.hpp>
#include <set>
#include <list>

class ShaderBinding;
class ShaderProgram;
class MeshBatched final : public MeshBase {
	public:
		MeshBatched(const Vertex::Format& format);
		virtual ~MeshBatched() override;
		MeshBatched(MeshBatched&& rhs);
		MeshBatched& operator=(MeshBatched&& rhs);

		void draw(const ShaderProgram* program) override;
		void draw(const ShaderProgram* program, unsigned int offset, unsigned int length);
		void draw(const ShaderProgram* program, unsigned int userData);
		void draw(const ShaderProgram* program, unsigned int offset, unsigned int length, unsigned int userData);
		void setVertexData(const void* vertexData, unsigned int newVertexCount) override;

		static void resetBatch();
		static void startBatch();
		static void endBatch();

		friend void swap(MeshBatched& a, MeshBatched& b);
	private:
		class Buffer {
			public:
				Buffer(const Vertex::Format& bufferFormat);
				~Buffer();

				void addMesh(MeshBatched* mesh);
				void deleteMesh(MeshBatched* mesh);
				void submitData(MeshBatched* mesh, const void* data, unsigned int vCount);
				unsigned int getMeshCount();
				unsigned long int getMeshOffset(MeshBatched* mesh);
				void setupBinding(const ShaderProgram* program);
				void bindBuffers() const;

				const Vertex::Format bufferFormat;
			private:
				struct Interval {
					Interval(unsigned int start, unsigned int count) : start(start), count(count) {}
					unsigned int start;
					unsigned int count;
				};

				void freeInterval(Interval i);
				Interval allocateInterval(unsigned int vCount);
				void resizeBuffer(unsigned int newSize);

				std::map<GLuint, const ShaderBinding*> bindings;
				GLuint vertexBuffer;
				unsigned int totalBufferSize; //in vertices
				std::list<Interval> freeIntervals; //in vertices
				std::map<MeshBatched*,Interval> usedIntervals; //in vertices
		};

		struct DrawIndirectCommand {
				GLuint vertexCount;
				GLuint instanceCount;
				GLuint firstVertex;
				GLuint firstInstance;
		};

		Buffer* getBuffer() const;

		static bool batching;
		static ShaderProgram* batchingProgram;
		static std::vector<DrawIndirectCommand> commands;
		static std::set<Buffer*> batches;

		friend class ShaderBinding;
};

#endif // MESHBATCHED_HPP
