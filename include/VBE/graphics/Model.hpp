#ifndef MODEL_HPP
#define MODEL_HPP

class ShaderProgram;
class Mesh;
class Model {
	public:
		Model();
		~Model();

		void draw() const;
		void draw(unsigned int offset, unsigned int length) const;

		mutable Mesh* mesh;
		mutable ShaderProgram* program;
};

#endif // MODEL_HPP
