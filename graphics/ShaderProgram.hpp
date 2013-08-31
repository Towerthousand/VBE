#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#include "Shader.hpp"

class Uniform;
class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		bool makeProgram(const std::string& vp_filename, const std::string& fp_filename);
		void attachShader(Shader &sh);
		bool link();
		void bind() const;
		void unbind() const;
		void printInfoLog();

		static void add(std::string name, ShaderProgram* program);
		static ShaderProgram* get(std::string name);

		//MATRIX
		void sendUniformMat4f(const std::string& uniformID
							  , const mat4f &mat) const;

		std::map<std::string,GLint> attributes;
		std::map<std::string,Uniform*> uniforms;

	private:
		GLuint programHandle;
		static std::map<std::string,ShaderProgram*> programs;
};


#endif // SHADERPROGRAM_HPP
