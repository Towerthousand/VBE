#ifndef SHADER_HPP
#define SHADER_HPP
#include "../tools.hpp"

class Shader : public NonCopyable  {
	public:
		~Shader();

		static Shader* loadShader(const std::string& data, GLenum shaderType);
		void attach(GLuint program) const;
	private:
		Shader(GLenum type);

		void loadFromFile(const std::string& filename);
		void loadFromString(const std::string& content);
		void compile() const;

		void printInfoLog() const;
		GLuint shaderHandle;
};
#endif // SHADER_HPP
