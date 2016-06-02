#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Shader.hpp>
#include <VBE/utils/NonCopyable.hpp>

class Shader;
class Uniform;
class ShaderProgram : public NonCopyable {
    public:
        ShaderProgram();

        ShaderProgram(std::vector<std::pair<Shader::Type, std::string>> shaders);

        ShaderProgram(const std::string &vert, const std::string &frag);
        ShaderProgram(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> frag);

#ifndef VBE_GLES2
        ShaderProgram(const std::string& vert, const std::string& geom, const std::string& frag);
        ShaderProgram(const std::string& vert, const std::string& tessControl, const std::string& tessEval, const std::string& geom, const std::string& frag);
        ShaderProgram(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> geom, std::unique_ptr<std::istream> frag);
        ShaderProgram(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> tessControl, std::unique_ptr<std::istream> tessEval, std::unique_ptr<std::istream> geom, std::unique_ptr<std::istream> frag);
#endif
        ~ShaderProgram();

        GLuint getHandle() const {return programHandle;}

        void use() const;
        bool hasUniform(const std::string& name) const;
        Uniform* uniform(const std::string& name) const;

        const std::map<std::string, GLint>& getAttributes() const { return attributes; }

        ShaderProgram(ShaderProgram&& rhs);
        ShaderProgram& operator=(ShaderProgram&& rhs);
        friend void swap(ShaderProgram& a, ShaderProgram& b);
    private:
        void link();
        void retrieveProgramInfo();
        void printInfoLog();

        GLuint programHandle = 0;
        std::map<std::string, GLint> attributes;
        std::map<std::string, Uniform*> uniforms;

        static GLuint current;
};


#endif // SHADERPROGRAM_HPP
