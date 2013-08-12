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
	private:
		mat4f modelMatrix;
		Mesh* mesh;
		//EffectBinding binding;
};

#endif // MODEL_HPP
