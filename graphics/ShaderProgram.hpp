#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "../tools.hpp"

class Shader;
class Uniform;
class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		void makeProgramFromString(const std::string &vertSource, const std::string &fragSource);
		void makeProgramFromString(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);
		void makeProgramFromFile(const std::string& vp_filename, const std::string& fp_filename);
		void makeProgramFromFile(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename);

		GLuint getHandle() const {return programHandle;}

		void use() const;
		Uniform* uniform(const std::string& name) const;

		std::map<std::string,GLint> attributes;
		std::map<std::string,Uniform*> uniforms;

	private:
		void makeProgram(const std::string& vp_filename, const std::string& fp_filename, bool raw);
		void makeProgram(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename, bool raw);
		void link();
		void retriveProgramInfo();
		void printInfoLog();

		static GLuint current;

		GLuint programHandle;
};


#endif // SHADERPROGRAM_HPP
