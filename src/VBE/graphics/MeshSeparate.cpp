#include <VBE/graphics/MeshSeparate.hpp>
#include <VBE/system/Log.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/graphics/ShaderBinding.hpp>

MeshSeparate::MeshSeparate() {
}

MeshSeparate::MeshSeparate(const Vertex::Format& format, BufferType bufferType) :
    MeshBase(format, bufferType) {
    GL_ASSERT(glGenBuffers(1, &vertexBuffer));
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, 0, nullptr, getBufferType()));
}

MeshSeparate::~MeshSeparate() {
    if(vertexBuffer != 0)
        GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
    for(std::map<GLuint, const ShaderBinding*>::iterator it = bindingsCache.begin(); it != bindingsCache.end(); ++it)
        delete it->second;
}

void MeshSeparate::bindBuffers() const {
    VBE_ASSERT(getVertexBuffer() != 0, "Cannot use empty mesh");
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
}

void MeshSeparate::setupShaderBinding(const ShaderProgram& program) const {
    VBE_ASSERT(getVertexBuffer() != 0, "Cannot use empty mesh");

    // Get the binding from the cache. If it does not exist, create it.
    GLuint handle = program.getHandle();
    if(bindingsCache.find(handle) == bindingsCache.end())
        bindingsCache.insert(std::pair<GLuint, const ShaderBinding*>(handle, new ShaderBinding(&program, this)));
    const ShaderBinding* binding = bindingsCache.at(handle);

    // Bind the program and the binding
    program.use();
    ShaderBinding::bind(binding);
}

GLuint MeshSeparate::getVertexBuffer() const {
    return vertexBuffer;
}

void MeshSeparate::setVertexData(const void* vertexData, unsigned int newVertexCount) {
    VBE_ASSERT(getVertexBuffer() != 0, "Cannot use empty mesh");

    // Bind null shader binding, so we don't change the buffer of the previously bound one.
    ShaderBinding::bind(nullptr);
    vertexCount = newVertexCount;
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, getVertexSize() * vertexCount, vertexData, getBufferType()));
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void MeshSeparate::setInstanceAttribsFormat(const Vertex::Format& format) {
    instanceDataFormat = format;
}

void MeshSeparate::setInstancesData(const void* instancesData, unsigned int instanceCount) {
    // create the buffer only if we ask to set per instance data, not on mesh creation
    if (instanceDataBuffer == 0) {
        GL_ASSERT(glGenBuffers(1, &instanceDataBuffer));
    }
    ShaderBinding::bind(nullptr);
    VBE_ASSERT(instanceDataBuffer != 0, "No instance buffer created for this mesh");
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer));
    GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, instanceDataFormat.vertexSize() * instanceCount, instancesData, MeshBase::DYNAMIC));
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

const Vertex::Format& MeshSeparate::getInstanceAttribsFormat() const {
    return instanceDataFormat;
}

void MeshSeparate::bindInstanceDataBuffer() const {
    VBE_ASSERT(getInstanceDataBuffer() != 0, "No instance buffer created for this mesh");
    GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer));
}

GLuint MeshSeparate::getInstanceDataBuffer() const {
    return instanceDataBuffer;
}


void swap(MeshSeparate& a, MeshSeparate& b) {
    using std::swap;
    swap(static_cast<MeshBase&>(a), static_cast<MeshBase&>(b));
    swap(a.bindingsCache, b.bindingsCache);
    swap(a.vertexBuffer, b.vertexBuffer);
    swap(a.instanceDataFormat, b.instanceDataFormat);
    swap(a.instanceDataBuffer, b.instanceDataBuffer);
}
