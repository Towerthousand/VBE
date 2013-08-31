#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#include "Shader.hpp"
#include "Uniform.hpp"

class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		bool makeProgram(const std::string& vp_filename, const std::string& fp_filename);

		static void useProgram(std::string name);
		static void add(std::string name, ShaderProgram* program);
		static void ready();
		static Uniform* uniform(std::string name);

		std::map<std::string,GLint> attributes;
		std::map<std::string,Uniform*> uniforms;

	private:
		void printInfoLog();
		GLuint programHandle;
		static ShaderProgram* currentProgram;
		static std::map<std::string,ShaderProgram*> programs;
};


#endif // SHADERPROGRAM_HPP
