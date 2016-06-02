#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <vector>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/math.hpp>

class Texture2D;
class Texture3D;
class Texture2DArray;
class TextureCubemap;
class TextureCubemapArray;
class Texture;

///
/// \brief The Uniform class represents an OpenGL ShaderProgram Uniform
///
class Uniform : public NonCopyable {
    public:
        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be an int, 2D sampler or bool
        ///
        void set(int val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be an int, 2D sampler or bool array of the same size
        ///
        void set(const std::vector<int> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a bool
        ///
        void set(bool val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a float
        ///
        void set(float val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a float array of the same size
        ///
        void set(const std::vector<float> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec2f
        ///
        void set(const vec2f &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec2f array of the same size
        ///
        void set(const std::vector<vec2f> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec3f
        ///
        void set(const vec3f &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec3f array of the same size
        ///
        void set(const std::vector<vec3f> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec4f
        ///
        void set(const vec4f &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec4f array of the same size
        ///
        void set(const std::vector<vec4f> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec2i
        ///
        void set(const vec2i &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec2i array of the same size
        ///
        void set(const std::vector<vec2i> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec3i
        ///
        void set(const vec3i &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec3i array of the same size
        ///
        void set(const std::vector<vec3i> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec4i
        ///
        void set(const vec4i &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a vec4i array of the same size
        ///
        void set(const std::vector<vec4i> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a mat3f
        ///
        void set(const mat3f &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a mat3f array of the same size
        ///
        void set(const std::vector<mat3f> &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a mat4
        ///
        void set(const mat4f &val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be a mat4 array of the same size
        ///
        void set(const std::vector<mat4f> &val);

        ///
        /// \brief Set contents of the uniform
        /// \param val Cannot be nullptr
        ///
        /// Uniform must be an 2D sampler
        ///
        void set(const Texture2D* val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be an 2D sampler
        ///
        void set(const Texture2D& val);

#ifndef VBE_GLES2

        ///
        /// \brief Set contents of the uniform
        /// \param val Cannot be nullptr
        ///
        /// Uniform must be an 3D sampler
        ///
        void set(const Texture3D* val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be an 3D sampler
        ///
        void set(const Texture3D& val);

        ///
        /// \brief Set contents of the uniform
        /// \param val Cannot be nullptr
        ///
        /// Uniform must be an 2D array sampler or a 2D array shadow sampler
        ///
        void set(const Texture2DArray* val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be an 2D array sampler or a 2D array shadow sampler
        ///
        void set(const Texture2DArray& val);

        ///
        /// \brief Set contents of the uniform
        /// \param val Cannot be nullptr
        ///
        /// Uniform must be an Cubemap sampler
        ///
        void set(const TextureCubemap* val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be an Cubemap sampler
        ///
        void set(const TextureCubemap& val);

        ///
        /// \brief Set contents of the uniform
        /// \param val Cannot be nullptr
        ///
        /// Uniform must be an Cubemap array sampler
        ///
        void set(const TextureCubemapArray* val);

        ///
        /// \brief Set contents of the uniform
        ///
        /// Uniform must be an Cubemap array sampler
        ///
        void set(const TextureCubemapArray& val);

#endif

        ///
        /// \brief Detailed log of this uniform as a Log::message.
        ///
        /// Will only log if VBE_DETAIL is defined
        ///
        void log();

    private:
        Uniform(unsigned int count, GLenum type, GLint location);
        ~Uniform();

        static bool isSampler(GLenum uniformType);

        void ready();
        void setBytes(const char* val);
        bool compare(const char* val) const;

        bool dirty = true;
        unsigned int count = 0;
        GLenum type = GL_FLOAT;
        GLint location = 0;
        unsigned int texUnit = -1; //only valid if sampler
        std::vector<char> lastValue;

        friend class ShaderProgram;
};
///
/// \class Uniform Uniform.hpp <VBE/graphics/Uniform.hpp>
///	\ingroup Graphics
///
///

#endif // UNIFORM_HPP
