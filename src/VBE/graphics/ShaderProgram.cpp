#include <cstring>
#include <string>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Shader.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/graphics/Uniform.hpp>
#include <VBE/system/Log.hpp>
#include <VBE/system/Storage.hpp>

GLuint ShaderProgram::current = 0;

ShaderProgram::ShaderProgram() {
}

ShaderProgram::ShaderProgram(std::vector<std::pair<Shader::Type, std::string>> shaders) {

    GL_ASSERT(programHandle = glCreateProgram());

    std::vector<Shader> parts;
    for(const auto& s : shaders) {
        Shader shader(s.first, s.second);
        shader.attach(programHandle);
        parts.push_back(std::move(shader));
    }

    link();
    retrieveProgramInfo();
}

ShaderProgram::~ShaderProgram() {
    if(programHandle != 0)
        GL_ASSERT(glDeleteProgram(programHandle));
    for(const auto& e : uniforms)
        delete e.second;
}


ShaderProgram::ShaderProgram(const std::string &vert, const std::string &frag) :
    ShaderProgram({std::pair<Shader::Type, std::string>(Shader::Type::Vertex, vert),
                  std::pair<Shader::Type, std::string>(Shader::Type::Fragment, frag)}) {
}

ShaderProgram::ShaderProgram(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> frag) :
    ShaderProgram(Storage::readToString(std::move(vert)),
                  Storage::readToString(std::move(frag))) {
}

#ifndef VBE_GLES2
ShaderProgram::ShaderProgram(const std::string& vert, const std::string& geom, const std::string& frag)
    : ShaderProgram({std::pair<Shader::Type, std::string>(Shader::Type::Vertex, vert),
                    std::pair<Shader::Type, std::string>(Shader::Type::Geometry, geom),
                    std::pair<Shader::Type, std::string>(Shader::Type::Fragment, frag)}) {
}

ShaderProgram::ShaderProgram(const std::string& vert, const std::string& tessControl, const std::string& tessEval, const std::string& geom, const std::string& frag)
    : ShaderProgram({std::pair<Shader::Type, std::string>(Shader::Type::Vertex, vert),
                    std::pair<Shader::Type, std::string>(Shader::Type::TessControl, tessControl),
                    std::pair<Shader::Type, std::string>(Shader::Type::TessEval, tessEval),
                    std::pair<Shader::Type, std::string>(Shader::Type::Geometry, geom),
                    std::pair<Shader::Type, std::string>(Shader::Type::Fragment, frag)}) {
}

ShaderProgram::ShaderProgram(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> geom, std::unique_ptr<std::istream> frag) :
    ShaderProgram(Storage::readToString(std::move(vert)),
                  Storage::readToString(std::move(geom)),
                  Storage::readToString(std::move(frag))) {
}
ShaderProgram::ShaderProgram(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> tessControl, std::unique_ptr<std::istream> tessEval, std::unique_ptr<std::istream> geom, std::unique_ptr<std::istream> frag) :
    ShaderProgram(Storage::readToString(std::move(vert)),
                  Storage::readToString(std::move(tessControl)),
                  Storage::readToString(std::move(tessEval)),
                  Storage::readToString(std::move(geom)),
                  Storage::readToString(std::move(frag))) {
}
#endif

void ShaderProgram::printInfoLog() {
    VBE_ASSERT(programHandle != 0, "Trying to query nullptr program");
    int length = 0;
    GL_ASSERT(glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &length));
    if (length > 1) {
        GLchar* infoLog = new GLchar[length];
        GL_ASSERT(glGetProgramInfoLog(programHandle, length, nullptr, infoLog));
        VBE_LOG(infoLog );
        delete[] infoLog;
    }
}

void ShaderProgram::use() const {
    VBE_ASSERT(programHandle != 0, "Trying to use null program");
    if(current != programHandle) {
        current = programHandle;
        GL_ASSERT(glUseProgram(programHandle));
    }
    for(std::map<std::string, Uniform*>::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
        it->second->ready();
}

bool ShaderProgram::hasUniform(const std::string &name) const {
    return uniforms.find(name) != uniforms.end();
}

Uniform* ShaderProgram::uniform(const std::string &name) const {
    VBE_ASSERT(uniforms.find(name) != uniforms.end(), "Trying to retrieve unexisting uniform " << name);
    VBE_ASSERT(programHandle != 0, "Trying to retrieve uniform from nullptr program");
    return uniforms.at(name);
}

void ShaderProgram::link() {
    GL_ASSERT(glLinkProgram(programHandle));
    //CHECK FOR LINK SUCCESS
    GLint success;
    GL_ASSERT(glGetProgramiv(programHandle, GL_LINK_STATUS, &success));
    if (success != GL_TRUE) {
        printInfoLog();
        VBE_ASSERT(false, "Linking program failed" );
    }
    VBE_DLOG( " - Linked program successfully. PROGRAMID: " << programHandle );
}

void ShaderProgram::retrieveProgramInfo() {
    //RETRIEVE ATTRIBUTE DATA
    GLint activeAttributes;
    GL_ASSERT(glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &activeAttributes));
    if (activeAttributes > 0) {
        GLint length;
        GL_ASSERT(glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length));
        if (length > 0) {
            GLchar* attribName = new GLchar[length + 1];
            GLint attribSize;
            GLenum attribType;
            GLint attribLocation;
            for (int i = 0; i < activeAttributes; ++i) {
                // Query attribute info.
                GL_ASSERT(glGetActiveAttrib(programHandle, i, length, nullptr, &attribSize, &attribType, attribName));
                attribName[length] = '\0';

                // Query the pre-assigned attribute location.
                attribLocation = glGetAttribLocation(programHandle, attribName);

                // Assign the vertex attribute mapping for the effect.
                attributes[attribName] = attribLocation;
            }
            delete[] attribName;
        }
    }

    //RETRIEVE UNIFORM INFO
    GLint activeUniforms;
    GL_ASSERT(glGetProgramiv(programHandle, GL_ACTIVE_UNIFORMS, &activeUniforms));
    if (activeUniforms > 0) {
        GLint length;
        GL_ASSERT(glGetProgramiv(programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length));
        if (length > 0) {
            GLchar* uniformName = new GLchar[length + 1];
            GLint uniformSize;
            GLenum uniformType;
            GLint uniformLocation;
            unsigned int texUnit = 0;
            for (int i = 0; i < activeUniforms; ++i) {
                // Query uniform info.
                GL_ASSERT(glGetActiveUniform(programHandle, i, length, nullptr, &uniformSize, &uniformType, uniformName));
                uniformName[length] = '\0';  // nullptr terminate
                if (uniformSize > 1 && length > 3) {
                    // This is an array uniform. I'm stripping array indexers off it since GL does not
                    // seem to be consistent across different drivers/implementations in how it returns
                    // array uniforms. On some systems it will return "u_matrixArray", while on others
                    // it will return "u_matrixArray[0]".

                    //TODO rewrite this using std::string please
                    char* c = strrchr(uniformName, '[');
                    if (c) *c = '\0';
                }

                // Query the pre-assigned uniform location.
                uniformLocation = glGetUniformLocation(programHandle, uniformName);
                VBE_ASSERT(glGetError() == GL_NO_ERROR, "Failed to get uniform location");
                Uniform* uniform = new Uniform(uniformSize, uniformType, uniformLocation);
                if(Uniform::isSampler(uniformType)) uniform->texUnit = texUnit++;
                uniforms[uniformName] = uniform;
            }
            delete[] uniformName;
        }
    }

    //PRINT ATTRIBUTE INFO
    VBE_DLOG(" - Printing attribute info:" );
    for(std::map<std::string, GLint>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
        VBE_DLOG("  - Name: " << it->first);
        VBE_DLOG( "    Location: " << it->second);
    }

    //PRINT UNIFORM INFO
    VBE_DLOG(" - Printing uniform info:" );
    for(std::map<std::string, Uniform*>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
        VBE_DLOG("  - Name: " << it->first);
        it->second->log();
    }
}

ShaderProgram::ShaderProgram(ShaderProgram&& rhs) : ShaderProgram() {
    using std::swap;
    swap(*this, rhs);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void swap(ShaderProgram& a, ShaderProgram& b) {
    using std::swap;

    swap(a.attributes, b.attributes);
    swap(a.uniforms, b.uniforms);
    swap(a.programHandle, b.programHandle);
}

