#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#include "Shader.hpp"
#include "Uniform.hpp"

class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		bool makeProgram(const std::string& vp_filename, const std::string& fp_filename);

		void use();
		Uniform* uniform(std::string name);

		std::map<std::string,GLint> attributes;
		std::map<std::string,Uniform*> uniforms;

	private:
		static GLint current;

		void printInfoLog();
		GLuint programHandle;
};


#endif // SHADERPROGRAM_HPP
