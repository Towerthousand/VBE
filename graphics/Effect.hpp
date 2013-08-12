#ifndef EFFECT_HPP
#define EFFECT_HPP

class ShaderProgram;
class Effect {
	public:
		Effect();
		~Effect();

	private:
		ShaderProgram* program;
};

#endif // EFFECT_HPP
