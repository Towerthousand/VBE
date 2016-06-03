#include <VBE/graphics/MeshBatched.hpp>
#include <algorithm>
#include <VBE/system/Log.hpp>
#include "ShaderBinding.hpp"

bool MeshBatched::batching = false;
MeshBatched::Buffer* MeshBatched::batchingBuffer = nullptr;
const ShaderProgram* MeshBatched::batchingProgram = nullptr;
MeshBase::PrimitiveType MeshBatched::batchingPrimitive = MeshBase::TRIANGLES;
GLuint MeshBatched::perDrawAttribBuffer = 0;
unsigned int MeshBatched::perDrawAttribBufferSize = 0;
GLuint MeshBatched::indirectBuffer = 0;
std::vector<MeshBatched::DrawIndirectCommand> MeshBatched::commands;
std::set<MeshBatched::Buffer*> MeshBatched::buffers;

MeshBatched::MeshBatched() : MeshBatched(Vertex::Format()) {
}

MeshBatched::MeshBatched(const Vertex::Format& format) : MeshBase(format, STREAM) {
    ensureInitBuffers();
    Buffer* b = getBuffer();
    if(b == nullptr) {
        b = new Buffer(format);
        buffers.insert(b);
    }
    b->addMesh(this);
}

MeshBatched::~MeshBatched() {
    Buffer* b = getBuffer();
    if(b->containsMesh(this)) {
        b->deleteMesh(this);
        if(b->getMeshCount() == 0) {
            buffers.erase(b);
            delete b;
        }
    }
}

MeshBatched::MeshBatched(MeshBatched&& rhs) : MeshBase(Vertex::Format(std::vector<Vertex::Attribute>())) {
    using std::swap;
    swap(*this, rhs);
}

MeshBatched& MeshBatched::operator=(MeshBatched&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void MeshBatched::draw(const ShaderProgram& program) const {
    draw(program, 0, vertexCount);
}

void MeshBatched::draw(const ShaderProgram& program, unsigned int offset, unsigned int length) const {
    VBE_ASSERT(program.getHandle() != 0, "program cannot be null");
    VBE_ASSERT(length != 0, "length must not be zero");
    VBE_ASSERT(offset < getVertexCount(), "offset must be smaller than vertex count");
    VBE_ASSERT(offset + length <= getVertexCount(), "offset plus length must be smaller or equal to vertex count");

    Buffer* b = getBuffer();
    b->setupBinding(&program);

    GL_ASSERT(glDrawArrays(getPrimitiveType(), b->getMeshOffset(this) + offset, length));
}

void MeshBatched::drawBatched(const ShaderProgram& program) const {
    drawBatched(program, 0, vertexCount);
}

void MeshBatched::drawBatched(const ShaderProgram& program, unsigned int offset, unsigned int length) const {
    VBE_ASSERT(batching, "Cannot draw a MeshBatched with batching without calling startBatch() first.");
    Buffer* b = getBuffer();
    if(batchingBuffer == nullptr) { //first command
        batchingBuffer = b;
        batchingProgram = &program;
        batchingPrimitive = getPrimitiveType();
    }
    VBE_ASSERT(batchingBuffer == b, "Cannot send two MeshBatched with different formats under the same batch.");
    VBE_ASSERT(batchingProgram == &program, "Cannot use two different programs during the same batch.");
    VBE_ASSERT(batchingPrimitive == getPrimitiveType(), "Cannot use two different primitives during the same batch.");
    commands.push_back(DrawIndirectCommand(length, 1, b->getMeshOffset(this) + offset, commands.size()));
}

void MeshBatched::setVertexData(const void* vertexData, unsigned int newVertexCount) {
    Buffer* b = getBuffer();
    vertexCount = newVertexCount;
    b->submitData(this, vertexData, newVertexCount);
}

void MeshBatched::resetBatch() {
    commands.clear();
}

void MeshBatched::startBatch() {
    VBE_ASSERT(!batching, "Cannot start a new batch without ending the previous one.");
    resetBatch();
    batching = true;
}

void MeshBatched::endBatch() {
    VBE_ASSERT(batching, "Cannot end a batch that wasn't started.");
    batching = false;
    if(commands.size() == 0) return;
    uploadPerDrawData(commands.size());
    uploadIndirectCommands();

    batchingBuffer->setupBinding(batchingProgram);
    GL_ASSERT(glMultiDrawArraysIndirect(batchingPrimitive, 0, commands.size(), 0));
    commands.clear();
    batchingBuffer = nullptr;
    batchingProgram = nullptr;
}

MeshBatched::Buffer* MeshBatched::getBuffer() const {
    for(Buffer* b : buffers)
        if(b->bufferFormat == getVertexFormat())
            return b;
    return nullptr;
}

void MeshBatched::ensureInitBuffers() {
    if(perDrawAttribBuffer == 0) {
        GL_ASSERT(glGenBuffers(1, &perDrawAttribBuffer));
        uploadPerDrawData(1);
    }
    if(indirectBuffer == 0) {
        GL_ASSERT(glGenBuffers(1, &indirectBuffer));
    }
}

void MeshBatched::uploadIndirectCommands() {
    GL_ASSERT(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBuffer));
    GL_ASSERT(glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawIndirectCommand)*commands.size(), &commands[0], STATIC));
}

void MeshBatched::uploadPerDrawData(unsigned int size) {
    if(size <= perDrawAttribBufferSize) return;
    perDrawAttribBufferSize = size;
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, perDrawAttribBuffer));
    GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, size*sizeof(unsigned int), 0, STATIC));
    GLuint* draw_index = nullptr;
    GL_ASSERT(draw_index = (GLuint *)glMapBufferRange(GL_ARRAY_BUFFER, 0, size * sizeof(GLuint),
                                                      GL_MAP_WRITE_BIT |
                                                      GL_MAP_INVALIDATE_BUFFER_BIT));
    VBE_ASSERT(draw_index != nullptr, "glMapBufferRange Failed!");
    for(unsigned int i = 0; i < size; i++)
        draw_index[i] = i;
    GL_ASSERT(glUnmapBuffer(GL_ARRAY_BUFFER));
}

void MeshBatched::bindPerDrawBuffers() {
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, perDrawAttribBuffer));
}

void swap(MeshBatched& a, MeshBatched& b) {
    using std::swap;
    MeshBatched::Buffer* bufA = a.getBuffer();
    VBE_ASSERT(bufA->containsMesh(&a), "Trying to get Mesh from batching buffer but the mesh is not in the Buffer");
    MeshBatched::Buffer* bufB = b.getBuffer();
    VBE_ASSERT(bufB->containsMesh(&b), "Trying to get Mesh from batching buffer but the mesh is not in the Buffer");
    MeshBatched::Buffer::Interval iA = bufA->usedIntervals.at(&a);
    bufA->usedIntervals.erase(&a);
    bufA->usedIntervals.insert(std::pair<MeshBatched*, MeshBatched::Buffer::Interval>(&b, iA));
    MeshBatched::Buffer::Interval iB = bufB->usedIntervals.at(&b);
    bufB->usedIntervals.erase(&b);
    bufB->usedIntervals.insert(std::pair<MeshBatched*, MeshBatched::Buffer::Interval>(&a, iB));
    swap(static_cast<MeshBase&>(a), static_cast<MeshBase&>(b));
}

MeshBatched::Buffer::Buffer(const Vertex::Format& format)
    : bufferFormat(format),
      vertexBuffer(0),
      totalBufferSize(1 << 10) {
    GL_ASSERT(glGenBuffers(1, &vertexBuffer));
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, totalBufferSize*bufferFormat.vertexSize(), 0, MeshBase::STREAM));
    freeInterval(Interval(0, 1 << 10));
}

MeshBatched::Buffer::~Buffer() {
    GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
}

void MeshBatched::Buffer::addMesh(MeshBatched* mesh) {
    usedIntervals.insert(std::pair<MeshBatched*, Interval>(mesh, Interval(0,0)));
}

void MeshBatched::Buffer::deleteMesh(MeshBatched* mesh) {
    VBE_ASSERT(this->containsMesh(mesh), "Trying to get Mesh from batching buffer but the mesh is not in the Buffer");
    freeInterval(usedIntervals.at(mesh));
    usedIntervals.erase(mesh);
}

void MeshBatched::Buffer::submitData(MeshBatched* mesh, const void* data, unsigned int vCount) {
    VBE_ASSERT(this->containsMesh(mesh), "Trying to get Mesh from batching buffer but the mesh is not in the Buffer");
    Interval& i = usedIntervals.at(mesh);
    freeInterval(i);
    i = Interval(0,0);
    i = allocateInterval(vCount);
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    GL_ASSERT(glBufferSubData(GL_ARRAY_BUFFER, i.start*bufferFormat.vertexSize(), vCount*bufferFormat.vertexSize(), data));
}

unsigned int MeshBatched::Buffer::getMeshCount() const {
    return usedIntervals.size();
}

unsigned long MeshBatched::Buffer::getMeshOffset(const MeshBatched* mesh) const {
    VBE_ASSERT(this->containsMesh(mesh), "Trying to get Mesh from batching buffer but the mesh is not in the Buffer");
    return usedIntervals.at(mesh).start;
}

void MeshBatched::Buffer::setupBinding(const ShaderProgram* program) {
    // Get the binding from the cache. If it does not exist, create it.
    GLuint handle = program->getHandle();
    if(bindings.find(handle) == bindings.end())
        bindings.insert(std::pair<GLuint, const ShaderBinding*>(handle, new ShaderBinding(program, this)));
    const ShaderBinding* binding = bindings.at(handle);

    // Bind the program and the binding
    program->use();
    ShaderBinding::bind(binding);
}

void MeshBatched::Buffer::bindBuffers() const {
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
}

void MeshBatched::Buffer::freeInterval(Interval i) {
    VBE_ASSERT(i.start + i.count <= totalBufferSize, "Free out of bounds GPU memory");
    if(i.count == 0) return;
    bool merged = false;
    //merge with previous one if possible
    std::set<Interval>::iterator lower = std::lower_bound(freeIntervals.begin(), freeIntervals.end(), i);
    if(lower != freeIntervals.end() && lower != freeIntervals.begin()) {
        --lower;
        Interval previous = *lower;
        if(previous.start + previous.count == i.start) {
            freeIntervals.erase(previous);
            previous.count += i.count;
            freeIntervals.insert(previous);
            i = previous;
            merged = true;
        }
    }
    //merge with next one if possible
    std::set<Interval>::iterator upper = std::upper_bound(freeIntervals.begin(), freeIntervals.end(), i);
    if(upper != freeIntervals.end()) {
        Interval next = *upper;
        if(next.start == i.start + i.count) {
            freeIntervals.erase(next);
            freeIntervals.erase(i);
            i.count += next.count;
            freeIntervals.insert(i);
            merged = true;
        }
    }
    //else, push it standalone
    if(!merged) freeIntervals.insert(i);
}

MeshBatched::Buffer::Interval MeshBatched::Buffer::allocateInterval(unsigned int vCount) {
    Interval ret(0, vCount);
    Interval toReplace(0,0);
    bool spaceAvailable = false;
    for(const Interval& i : freeIntervals) {
        if(i.count >= vCount) {
            toReplace = i;
            spaceAvailable = true;
            break;
        }
    }
    if(spaceAvailable) {
        ret.start = toReplace.start;
        freeIntervals.erase(toReplace);
        if(toReplace.count > vCount)
            freeIntervals.insert(Interval(toReplace.start + vCount, toReplace.count - vCount));
    }
    else {
        //buffer must be resized
        ret.start = totalBufferSize;
        int newSize = totalBufferSize;
        while(vCount > newSize-totalBufferSize) newSize *= 2;
        resizeBuffer(newSize);
        ret = allocateInterval(vCount); //...meh
    }
    return ret;
}

void MeshBatched::Buffer::resizeBuffer(unsigned int newSize) {
    VBE_ASSERT(newSize > totalBufferSize, "Cannot resize to a smaller size");
    //copy contents into new buffer
    GLuint newVBO = 0;
    GL_ASSERT(glGenBuffers(1, &newVBO));
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, newVBO));
    GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, newSize*bufferFormat.vertexSize(), 0, MeshBase::STREAM));
    GL_ASSERT(glBindBuffer(GL_COPY_READ_BUFFER, vertexBuffer));
    GL_ASSERT(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0, bufferFormat.vertexSize()*totalBufferSize));
    GL_ASSERT(glInvalidateBufferData(vertexBuffer));
    GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
    for(std::pair<const GLuint, const ShaderBinding*> bind : bindings) delete bind.second;
    bindings.clear();
    vertexBuffer = newVBO;
    unsigned int oldSize = totalBufferSize;
    totalBufferSize = newSize;
    //Mark the new memory as free
    freeInterval(Interval(oldSize, totalBufferSize-oldSize));
}
