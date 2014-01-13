#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#include "../tools.hpp"

class Texture2D;
class Texture3D;
class Uniform {
	public:
		Uniform(unsigned int count, GLenum type, GLint location);
		~Uniform();

		void set(int val);
		void set(const std::vector<int> &val);

		void set(float val);
		void set(const std::vector<float> &val);

		void set(const vec2f &val);
		void set(const std::vector<vec2f> &val);

		void set(const vec3f &val);
		void set(const std::vector<vec3f> &val);

		void set(const vec4f &val);
		void set(const std::vector<vec4f> &val);

		void set(const mat4f &val);
		void set(const std::vector<mat4f> &val);

		void set(const Texture2D* val);
		void set(const Texture3D* val);

		void log();

	private:
		void ready();
		void setBytes(const char* val);
		bool compare(const char* val) const;

		bool dirty;
		unsigned int count;
		GLenum type;
		GLint location;
		std::vector<char> lastValue;

		friend class ShaderProgram;
};

#endif // UNIFORM_HPP
