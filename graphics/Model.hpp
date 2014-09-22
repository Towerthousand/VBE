#ifndef MODEL_HPP
#define MODEL_HPP
#include "../tools.hpp"

class ShaderProgram;
class Mesh;
class Model {
	public:
		Model();
		~Model();

		void draw() const;
		void draw(unsigned int firstVertex, unsigned int vertexCount) const;

		mutable Mesh* mesh;
		mutable ShaderProgram* program;
};

#endif // MODEL_HPP
