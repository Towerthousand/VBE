#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#include "tools.hpp"

class Uniform {
	public:
		Uniform(unsigned int count, GLenum type, GLint location);
		~Uniform();

		void set(int val);
		void set(std::vector<int> val);

		void set(float val);
		void set(std::vector<float> val);

		void set(vec3f val);
		void set(std::vector<vec3f> val);

		void set(mat4f val);
		void set(std::vector<mat4f> val);

		void log();

	private:
		void ready();
		void setBytes(char* val);
		bool compare(char* val) const;

		bool dirty;
		unsigned int count;
		GLenum type;
		GLint location;
		std::vector<char> lastValue;

		friend class ShaderProgram;
};

#endif // UNIFORM_HPP
