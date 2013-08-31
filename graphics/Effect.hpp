#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "tools.hpp"

class ShaderProgram;
class Effect {
	public:
		Effect();
		~Effect();

	private:
		ShaderProgram* program;
};

#endif // EFFECT_HPP
