#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "../tools.hpp"

class Shader;
class Uniform;
class ShaderProgram {
	public:
		~ShaderProgram();

		static ShaderProgram* loadFromString(const std::string &vertSource, const std::string &fragSource);
		static ShaderProgram* loadFromString(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);
		static ShaderProgram* loadFromFile(const std::string& vp_filename, const std::string& fp_filename);
		static ShaderProgram* loadFromFile(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename);

		GLuint getHandle() const {return programHandle;}

		void use() const;
		Uniform* uniform(const std::string& name) const;

		std::map<std::string, GLint> attributes;
		std::map<std::string, Uniform*> uniforms;

	private:
		ShaderProgram();

		void link();
		void retriveProgramInfo();
		void printInfoLog();
		static std::string readFileIntoString(const std::string& filename);

		static GLuint current;

		GLuint programHandle;
};


#endif // SHADERPROGRAM_HPP
