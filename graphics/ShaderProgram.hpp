#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "../tools.hpp"

class Shader;
class Uniform;
class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		void makeProgram(const std::string& vp_filename, const std::string& fp_filename, bool raw);
		void makeProgram(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename, bool raw);

		GLuint getHandle() const {return programHandle;}

		void use() const;
		Uniform* uniform(const std::string& name) const;

		std::map<std::string,GLint> attributes;
		std::map<std::string,Uniform*> uniforms;

	private:
		void link();
		void retriveProgramInfo();
		void printInfoLog();

		static GLuint current;

		GLuint programHandle;
};


#endif // SHADERPROGRAM_HPP
