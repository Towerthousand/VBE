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

		Mesh* mesh;
		mutable ShaderProgram* program;
};

#endif // MODEL_HPP
