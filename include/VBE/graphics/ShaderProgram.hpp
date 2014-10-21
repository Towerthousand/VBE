#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <map>
#include <string>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/utils/NonCopyable.hpp>

class Shader;
class Uniform;
class ShaderProgram : public NonCopyable {
	public:
		~ShaderProgram();

		static ShaderProgram* loadFromString(const std::string &vertSource, const std::string &fragSource);
		static ShaderProgram* loadFromFile(const std::string& vp_filename, const std::string& fp_filename);

#ifndef VBE_GLES2
		static ShaderProgram* loadFromString(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);
		static ShaderProgram* loadFromString(const std::string& vertSource, const std::string& tescSource, const std::string& teseSource, const std::string& geomSource, const std::string& fragSource);
		static ShaderProgram* loadFromFile(const std::string& vp_filename, const std::string& gp_filename, const std::string& fp_filename);
		static ShaderProgram* loadFromFile(const std::string& vp_filename, const std::string& tc_filename, const std::string& te_filename, const std::string& gp_filename, const std::string& fp_filename);
#endif

		GLuint getHandle() const {return programHandle;}

		void use() const;
		bool hasUniform(const std::string& name) const;
		Uniform* uniform(const std::string& name) const;

		const std::map<std::string, GLint>& getAttributes() const { return attributes; }
	private:
		ShaderProgram();

		void link();
		void retrieveProgramInfo();
		void printInfoLog();

		GLuint programHandle;
		std::map<std::string, GLint> attributes;
		std::map<std::string, Uniform*> uniforms;

		static std::string readFileIntoString(const std::string& filename);
		static GLuint current;
};


#endif // SHADERPROGRAM_HPP
