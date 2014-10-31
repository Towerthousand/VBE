#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <map>
#include <memory>
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
		static ShaderProgram* load(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> frag);

#ifndef VBE_GLES2
		static ShaderProgram* loadFromString(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);
		static ShaderProgram* loadFromString(const std::string& vertSource, const std::string& tescSource, const std::string& teseSource, const std::string& geomSource, const std::string& fragSource);
		static ShaderProgram* load(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> geom, std::unique_ptr<std::istream> frag);
		static ShaderProgram* load(std::unique_ptr<std::istream> vert, std::unique_ptr<std::istream> tessControl, std::unique_ptr<std::istream> tessEval, std::unique_ptr<std::istream> geom, std::unique_ptr<std::istream> frag);
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

		static std::string readFileIntoString(std::unique_ptr<std::istream> file);
		static GLuint current;
};


#endif // SHADERPROGRAM_HPP
