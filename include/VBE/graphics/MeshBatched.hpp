#ifndef MESHBATCHED_HPP
#define MESHBATCHED_HPP
#include <VBE/graphics/MeshBase.hpp>
#include <set>
#include <list>

class ShaderBinding;
class ShaderProgram;
class MeshBatched final : public MeshBase {
    public:
        MeshBatched();
        MeshBatched(const Vertex::Format& format);
        virtual ~MeshBatched() override;
        MeshBatched(MeshBatched&& rhs);
        MeshBatched& operator=(MeshBatched&& rhs);

        void draw(const ShaderProgram& program) const override;
        void draw(const ShaderProgram& program, unsigned int offset, unsigned int length) const;
        void drawBatched(const ShaderProgram& program) const;
        void drawBatched(const ShaderProgram& program, unsigned int offset, unsigned int length) const;
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
                unsigned int getMeshCount() const;
                unsigned long int getMeshOffset(const MeshBatched* mesh) const;
                void setupBinding(const ShaderProgram* program);
                void bindBuffers() const;
                bool containsMesh(const MeshBatched* mesh) const {
                    return (usedIntervals.find(mesh) != usedIntervals.end());
                }

                const Vertex::Format bufferFormat;
            private:
                struct Interval {
                        Interval(unsigned int start, unsigned int count) : start(start), count(count) {}
                        bool operator <(const Interval& i) const {
                            return (start < i.start || (start == i.start && count < i.count));
                        }
                        unsigned int start;
                        unsigned int count;
                };

                void freeInterval(Interval i);
                Interval allocateInterval(unsigned int vCount);
                void resizeBuffer(unsigned int newSize);

                std::map<GLuint, const ShaderBinding*> bindings;
                GLuint vertexBuffer;
                unsigned int totalBufferSize; //in vertices
                std::set<Interval> freeIntervals; //in vertices
                std::map<const MeshBatched*,Interval> usedIntervals; //in vertices

                friend void swap(MeshBatched& a, MeshBatched& b);
        };

        struct DrawIndirectCommand {
                DrawIndirectCommand(GLuint vC, GLuint iC, GLuint fV, GLuint fI)
                    : vertexCount(vC), instanceCount(iC), firstVertex(fV), firstInstance(fI) {}
                GLuint vertexCount;
                GLuint instanceCount;
                GLuint firstVertex;
                GLuint firstInstance;
        };

        Buffer* getBuffer() const;
        static void ensureInitBuffers();
        static void uploadIndirectCommands();
        static void uploadPerDrawData(unsigned int size);
        static void bindPerDrawBuffers();

        //data about current batch (if any)
        static bool batching;
        static Buffer* batchingBuffer;
        static const ShaderProgram* batchingProgram;
        static PrimitiveType batchingPrimitive;
        //instanced vertex attrib data
        static GLuint perDrawAttribBuffer;
        static unsigned int perDrawAttribBufferSize;
        //draw indirect command buffer data
        static GLuint indirectBuffer;
        static std::vector<DrawIndirectCommand> commands;
        //all existing buffers (one per format)
        static std::set<Buffer*> buffers;

        friend class ShaderBinding;
};

#endif // MESHBATCHED_HPP
