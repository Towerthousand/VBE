#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "../tools.hpp"

class Uniform;
class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		bool makeProgramFromString(const std::string &vertSource, const std::string &fragSource);
		bool makeProgramFromString(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);

		bool makeProgram(const std::string& vp_filename, const std::string& fp_filename);
		bool makeProgram(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename);

		GLuint getHandle() const {return programHandle;}

		void use() const;
		Uniform* uniform(const std::string& name) const;

		std::map<std::string,GLint> attributes;
		std::map<std::string,Uniform*> uniforms;

	private:
		static GLuint current;

		void printInfoLog();
		GLuint programHandle;
};


#endif // SHADERPROGRAM_HPP
