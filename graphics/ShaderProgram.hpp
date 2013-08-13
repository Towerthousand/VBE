#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#include "Shader.hpp"

class Uniform {
	public:
		Uniform(unsigned int count, GLint location) : size(0), count(count), location(location), lastValue(NULL) {}
		bool compare(char* val, unsigned int size);
		void set(char* val, unsigned int size);
		void log() {std::cout << size << " bytes per item in an array of "
							  << count << " at location "
							  << location << std::endl;}

	private:
		unsigned int size;
		unsigned int count;
		GLint location;
		char* lastValue;
};

class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		bool makeProgram(const std::string& vp_filename, const std::string& fp_filename);
		void attachShader(Shader &sh);
		bool link();
		void bindLocation(uint index,const std::string& location);
		void bind() const;
		void unbind() const;
		GLint getUniLoc(const std::string &uniformID) const;
		void printInfoLog();

		//FLOAT
		void sendUniform1f(const std::string& uniformID
					  , float x) const;
		void sendUniform2f(const std::string& uniformID
					  , const vec2f& v) const;
		void sendUniform2f(const std::string& uniformID
					  , float x, float y) const;
		void sendUniform3f(const std::string& uniformID
					  , const vec3f& v) const;
		void sendUniform3f(const std::string& uniformID
					  , float x, float y, float z) const;
		void sendUniform4f(const std::string& uniformID
					  , const vec4f& v) const;
		void sendUniform4f(const std::string& uniformID
					  , float x, float y, float z, float w) const;

		//INTEGER
		void sendUniform1i(const std::string& uniformID
					  , int x) const;
		void sendUniform2i(const std::string& uniformID
					  , const vec2i& v) const;
		void sendUniform2i(const std::string& uniformID
					  , int x, int y) const;
		void sendUniform3i(const std::string& uniformID
					  , const vec3i& v) const;
		void sendUniform3i(const std::string& uniformID
					  , int x, int y, int z) const;
		void sendUniform4i(const std::string& uniformID
					  , const vec4i& v) const;
		void sendUniform4i(const std::string& uniformID
					  , int x, int y, int z, int w) const;

		//UNSIGNED INTEGER
		void sendUniform1ui(const std::string& uniformID
					   , uint x) const;
		void sendUniform2ui(const std::string& uniformID
					  , const vec2ui& v) const;
		void sendUniform2ui(const std::string& uniformID
					   , uint x, uint y) const;
		void sendUniform3ui(const std::string& uniformID
					  , const vec3ui& v) const;
		void sendUniform3ui(const std::string& uniformID
					   , uint x, uint y, uint z) const;
		void sendUniform4ui(const std::string& uniformID
					  , const vec4ui& v) const;
		void sendUniform4ui(const std::string& uniformID
					   , uint x, uint y, uint z, uint w) const;

		//MATRIX
		void sendUniformMat2f(const std::string& uniformID
							  , const mat2f &mat) const;
		void sendUniformMat3f(const std::string& uniformID
							  , const mat3f &mat) const;
		void sendUniformMat4f(const std::string& uniformID
							  , const mat4f &mat) const;

	private:
		GLuint programHandle;
		std::map<std::string,Uniform*> uniforms;
};


#endif // SHADERPROGRAM_HPP
