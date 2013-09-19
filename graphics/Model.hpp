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

		mat4f m_modelMatrix;
		Mesh* m_mesh;
		ShaderProgram* m_program;
};

#endif // MODEL_HPP
