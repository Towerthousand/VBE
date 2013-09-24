#ifndef SHADERBINDING_HPP
#define SHADERBINDING_HPP
#include "../tools.hpp"

class Mesh;
class ShaderProgram;
class ShaderBinding {
	public:
		ShaderBinding(const ShaderProgram* program, const Mesh* mesh);
		~ShaderBinding();

		void bindVAO() const;
	private:
		static GLuint currentVAO;
		GLuint vertexArrayObject;
};

#endif // SHADERBINDING_HPP
