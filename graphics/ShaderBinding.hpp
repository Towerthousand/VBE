#ifndef SHADERBINDING_HPP
#define SHADERBINDING_HPP
#include "../tools.hpp"

#ifndef VBE_GLES2
#define SHADERBINDING_USE_VAO
#endif

class Mesh;
class ShaderProgram;
class ShaderBinding : public NonCopyable {
	public:
		ShaderBinding(const ShaderProgram* program, const Mesh* mesh);
		~ShaderBinding();

		void enable() const;
	private:
		void applyAttributes() const;

		const ShaderProgram* program;
		const Mesh* mesh;

#ifdef SHADERBINDING_USE_VAO
		static GLuint currentVAO;
		GLuint vertexArrayObject;
#endif
};

#endif // SHADERBINDING_HPP
