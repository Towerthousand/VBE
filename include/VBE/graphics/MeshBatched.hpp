#ifndef MESHBATCHED_HPP
#define MESHBATCHED_HPP
#include <VBE/graphics/MeshBase.hpp>

//WIP

class ShaderBinding;
class ShaderProgram;
class MeshBatched final : public MeshBase {
	public:
		MeshBatched(const Vertex::Format& format);
		virtual ~MeshBatched() override;
		MeshBatched(MeshBatched&& rhs);
		MeshBatched& operator=(MeshBatched&& rhs);

		void draw(const ShaderProgram* program) override;
		void draw(const ShaderProgram* program, unsigned int userData);
		void draw(const ShaderProgram* program, unsigned int offset, unsigned int length);
		void draw(const ShaderProgram* program, unsigned int offset, unsigned int length, unsigned int userData);
		void setVertexData(const void* vertexData, unsigned int newVertexCount) override;

		static void resetBatch();
		static void startBatch();
		static void endBatch();

		friend void swap(MeshBatched& a, MeshBatched& b);
	private:
		struct MeshBatch {
				MeshBatch(const Vertex::Format& format);
				~MeshBatch();

				Vertex::Format format;
				std::map<GLuint, const ShaderBinding*> bindingsCache;
				GLuint vertexBuffer;
				std::vector<MeshBatched*> meshes;
		};

		struct DrawIndirectCommand {
				GLuint vertexCount;
				GLuint instanceCount;
				GLuint firstVertex;
				GLuint firstInstance;
		};

		static bool batching;
		static std::vector<DrawIndirectCommand> commands;
		static std::vector<MeshBatch*> batches;
};

#endif // MESHBATCHED_HPP
