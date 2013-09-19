#ifndef SHADER_HPP
#define SHADER_HPP
#include "../tools.hpp"

class Shader {
	public:
		Shader(GLenum type);
		~Shader();

		bool load(const std::string &filename);
		bool compile() const;

		void attach(GLuint program) const;
		void printInfoLog() const;

	private:
		GLuint shaderHandle;
};
#endif // SHADER_HPP
