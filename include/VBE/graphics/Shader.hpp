#ifndef SHADER_HPP
#define SHADER_HPP

#include <VBE/graphics/OpenGL.hpp>
#include <VBE/utils/NonCopyable.hpp>
#include <string>

class Shader : public NonCopyable  {
    public:

        enum Type {
            Vertex = GL_VERTEX_SHADER,
            TessControl = GL_TESS_CONTROL_SHADER,
            TessEval = GL_TESS_EVALUATION_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
        };

        Shader();
        Shader(Type type, const std::string& data);
        ~Shader();

        void attach(GLuint program) const;

        Shader(Shader&& rhs);
        Shader& operator=(Shader&& rhs);
        friend void swap(Shader& a, Shader& b);

    private:
        void loadFromString(const std::string& content);
        void compile() const;
        void printInfoLog() const;

        GLuint shaderHandle = 0;
};
#endif // SHADER_HPP
