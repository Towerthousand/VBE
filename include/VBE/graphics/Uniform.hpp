#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <vector>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/math.hpp>

class Texture2D;
class Texture3D;
class Texture2DArray;
class Texture;
class Uniform : public NonCopyable {
	public:
		Uniform(unsigned int count, GLenum type, GLint location);
		~Uniform();

		void set(int val);
		void set(const std::vector<int> &val);

		void set(bool val);

		void set(float val);
		void set(const std::vector<float> &val);

		void set(const vec2f &val);
		void set(const std::vector<vec2f> &val);

		void set(const vec3f &val);
		void set(const std::vector<vec3f> &val);

		void set(const vec4f &val);
		void set(const std::vector<vec4f> &val);

		void set(const vec2i &val);
		void set(const std::vector<vec2i> &val);

		void set(const vec3i &val);
		void set(const std::vector<vec3i> &val);

		void set(const vec4i &val);
		void set(const std::vector<vec4i> &val);
		
		void set(const mat3f &val);
		void set(const std::vector<mat3f> &val);

		void set(const mat4f &val);
		void set(const std::vector<mat4f> &val);
		
		void set(const Texture2D* val);
		void set(const Texture2D& val);
#ifndef VBE_GLES2
		void set(const Texture3D* val);
		void set(const Texture3D& val);
		void set(const Texture2DArray* val);
		void set(const Texture2DArray& val);
#endif

		void log();

	private:
		static bool isSampler(GLenum uniformType);

		void ready();
		void setBytes(const char* val);
		bool compare(const char* val) const;

		bool dirty;
		unsigned int count;
		GLenum type;
		GLint location;
		unsigned int texUnit; //only valid if sampler
		std::vector<char> lastValue;

		friend class ShaderProgram;
};

#endif // UNIFORM_HPP
