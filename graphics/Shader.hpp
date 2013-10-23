#ifndef SHADER_HPP
#define SHADER_HPP
#include "../tools.hpp"

class Shader {
	public:
		~Shader();

		static Shader* makeShader(const std::string& location, GLenum shaderType, bool raw);
		void attach(GLuint program) const;
	private:
		Shader(GLenum type);

		void load(const std::string &filename);
		void loadRaw(const std::string& content);
		void compile() const;

		void printInfoLog() const;
		GLuint shaderHandle;
};
#endif // SHADER_HPP
