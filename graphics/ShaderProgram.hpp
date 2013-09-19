#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "../tools.hpp"

class Uniform;
class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		bool makeProgram(const std::string& vp_filename, const std::string& fp_filename);
		GLuint getHandle() const {return m_programHandle;}

		void use() const;
		Uniform* uniform(const std::string& name) const;

		std::map<std::string,GLint> m_attributes;
		std::map<std::string,Uniform*> m_uniforms;

	private:
		static GLuint s_current;

		void printInfoLog();
		GLuint m_programHandle;
};


#endif // SHADERPROGRAM_HPP
