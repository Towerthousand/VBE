#ifndef MODEL_HPP
#define MODEL_HPP
#include "tools.hpp"

class Mesh;
class Model {
	public:
		Model();
		~Model();

		void setMesh(Mesh* m);
		Mesh* getMesh() const { return mesh;}

		void draw() const;

		mat4f modelMatrix;
	private:
		Mesh* mesh;
		//EffectBinding binding;
};

#endif // MODEL_HPP
