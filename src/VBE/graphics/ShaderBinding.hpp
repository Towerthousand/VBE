#ifndef SHADERBINDING_HPP
#define SHADERBINDING_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/utils/NonCopyable.hpp>

#ifndef VBE_GLES2
#define SHADERBINDING_USE_VAO
#endif

class MeshBase;
class ShaderProgram;
class ShaderBinding : public NonCopyable {
	public:
		ShaderBinding(const ShaderProgram* program, const MeshBase* mesh);
		~ShaderBinding();

		// Binds a ShaderBinding.
		static void bind(const ShaderBinding* binding);
	private:
		void enableAttributes() const;
		void disableAttributes() const;

		const ShaderProgram* program;
		const MeshBase* mesh;

		static const ShaderBinding* currentBind;

#ifdef SHADERBINDING_USE_VAO
		GLuint vertexArrayObject;
#endif
};

#endif // SHADERBINDING_HPP
