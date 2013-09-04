#ifndef MODEL_HPP
#define MODEL_HPP
#include "tools.hpp"

class ShaderProgram;
class Mesh;
class Model {
	public:
		Model();
		~Model();

		void draw() const;

		mat4f modelMatrix;
		Mesh* mesh;
		ShaderProgram* program;
	private:
		//EffectBinding binding;
};

#endif // MODEL_HPP
