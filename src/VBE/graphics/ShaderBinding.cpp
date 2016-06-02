#include <VBE/config.hpp>
#include <VBE/graphics/MeshSeparate.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/ShaderBinding.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/system/Log.hpp>

#ifdef SHADERBINDING_USE_VAO
#endif

ShaderBinding::ShaderBinding(const ShaderProgram* program, const MeshSeparate* mesh)
    : program(program), mesh(mesh), buffer(nullptr) {
    VBE_DLOG("* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh );
#ifdef SHADERBINDING_USE_VAO
    GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject));
    GL_ASSERT(glBindVertexArray(vertexArrayObject));
    enableAttributes();
#endif
}

ShaderBinding::ShaderBinding(const ShaderProgram* program, const MeshBatched::Buffer* buffer)
    : program(program), mesh(nullptr), buffer(buffer) {
    VBE_DLOG("* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh );
#ifdef SHADERBINDING_USE_VAO
    GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject));
    GL_ASSERT(glBindVertexArray(vertexArrayObject));
    enableAttributes();
#endif
}

ShaderBinding::~ShaderBinding() {
#ifdef SHADERBINDING_USE_VAO
    GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject));
#endif
}

const ShaderBinding* ShaderBinding::currentBind = nullptr;

void ShaderBinding::bind(const ShaderBinding* binding) {
    if(binding == currentBind) return;

#ifdef SHADERBINDING_USE_VAO
    if(binding != nullptr)
        GL_ASSERT(glBindVertexArray(binding->vertexArrayObject));
    else
        GL_ASSERT(glBindVertexArray(0));
#else
    if(currentBind != nullptr)
        currentBind->disableAttributes();
    if(binding != nullptr)
        binding->enableAttributes();
#endif
    currentBind = binding;
}

void ShaderBinding::enableAttributes() const {
    if(mesh != nullptr) mesh->bindBuffers();
    else buffer->bindBuffers();

    const Vertex::Format& format = (mesh != nullptr ? mesh->getVertexFormat() : buffer->bufferFormat);
    for(const std::pair<std::string, GLint>& attr: program->getAttributes()) {
#ifndef VBE_GLES2
        if(attr.first == "draw_index") {
            VBE_ASSERT(mesh == nullptr, "draw_index name used for vertex attribute on a program that's used in a non-batched mesh");
            MeshBatched::bindPerDrawBuffers();
            GL_ASSERT(glEnableVertexAttribArray(attr.second));
            GL_ASSERT(glVertexAttribIPointer(attr.second, 1, GL_UNSIGNED_INT, 0, 0));
            GL_ASSERT(glVertexAttribDivisor(attr.second, 1));
            buffer->bindBuffers();
        }
#endif
        for(unsigned int i = 0; i < format.elementCount(); ++i) {
            const Vertex::Attribute* current = &format.element(i);
            if(current->hasName(attr.first)) {
                GL_ASSERT(glEnableVertexAttribArray(attr.second));
#ifndef VBE_GLES2
                if(current->conv == Vertex::Attribute::ConvertToInt)
                    GL_ASSERT(glVertexAttribIPointer(attr.second,
                                                     current->size,
                                                     current->type,
                                                     format.vertexSize(),
                                                     (GLvoid*)long(format.offset(i))));
                else
#endif
                    GL_ASSERT(glVertexAttribPointer(attr.second,
                                                    current->size,
                                                    current->type, current->conv == Vertex::Attribute::ConvertToFloatNormalized ? GL_TRUE : GL_FALSE,
                                                    format.vertexSize(),
                                                    (GLvoid*)long(format.offset(i))));
            }
        }
    }

    // instancing data format
    if (mesh != nullptr && mesh->getInstanceAttribsFormat().elementCount() > 0) {
        mesh->bindInstanceDataBuffer();
        const Vertex::Format& instFormat = mesh->getInstanceAttribsFormat();
        for (const std::pair<std::string, GLint>& attr : program->getAttributes()) {
            for (unsigned int i = 0; i < instFormat.elementCount(); ++i) {
                const Vertex::Attribute* current = &instFormat.element(i);
                if (current->hasName(attr.first)) {
                    GL_ASSERT(glEnableVertexAttribArray(attr.second));
#ifndef VBE_GLES2
                    if (current->conv == Vertex::Attribute::ConvertToInt)
                        GL_ASSERT(glVertexAttribIPointer(attr.second,
                                                         current->size,
                                                         current->type,
                                                         instFormat.vertexSize(),
                                                         (GLvoid*)long(instFormat.offset(i))));
                    else
#endif
                        GL_ASSERT(glVertexAttribPointer(attr.second,
                                                        current->size,
                                                        current->type, current->conv == Vertex::Attribute::ConvertToFloatNormalized ? GL_TRUE : GL_FALSE,
                                                        instFormat.vertexSize(),
                                                        (GLvoid*)long(instFormat.offset(i))));

                    GL_ASSERT(glVertexAttribDivisor(attr.second, current->divisor));
                }
            }
        }
    }
}

void ShaderBinding::disableAttributes() const {
    VBE_ASSERT(mesh != nullptr, "Mesh cannot be nullptr");
    VBE_ASSERT(program != nullptr, "Program cannot be nullptr");

    const Vertex::Format format = mesh->getVertexFormat();
    for(const std::pair<std::string, GLint>& attr: program->getAttributes()) {
        for(unsigned int i = 0; i < format.elementCount(); ++i) {
            const Vertex::Attribute* current = &format.element(i);
            if(current->hasName(attr.first)) {
                GL_ASSERT(glDisableVertexAttribArray(attr.second));
            }
        }
    }
}
