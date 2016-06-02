#ifndef SHADERBINDING_HPP
#define SHADERBINDING_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/utils/NonCopyable.hpp>
#include <VBE/graphics/MeshSeparate.hpp>
#include <VBE/graphics/MeshBatched.hpp>

#ifndef VBE_GLES2
#define SHADERBINDING_USE_VAO
#endif

class ShaderBinding : public NonCopyable {
    public:
        ShaderBinding(const ShaderProgram* program, const MeshSeparate* mesh);
        ShaderBinding(const ShaderProgram* program, const MeshBatched::Buffer* buffer);
        ~ShaderBinding();

        // Binds a ShaderBinding.
        static void bind(const ShaderBinding* binding);
    private:
        void enableAttributes() const;
        void disableAttributes() const;

        //TODO: Fix this with handles!
        //Having pointers will wreck everything if the user moves the
        //resource after assigning it. For safety, handles should be
        //applied.
        const ShaderProgram* program;
        const MeshSeparate* mesh;
        const MeshBatched::Buffer* buffer;

        static const ShaderBinding* currentBind;

#ifdef SHADERBINDING_USE_VAO
        GLuint vertexArrayObject;
#endif
};

#endif // SHADERBINDING_HPP
