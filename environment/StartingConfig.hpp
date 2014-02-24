#ifndef STARTINGCONFIG_HPP
#define STARTINGCONFIG_HPP
#include "tools.hpp"

class StartingConfig {
	public:
		enum GLContextFlag {
			GLDebugContext = SDL_GL_CONTEXT_DEBUG_FLAG,
			GLForwardCompatibleContext = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,
			GLRobustAccessContext = SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG,
			GLRobustIsolationContext = SDL_GL_CONTEXT_RESET_ISOLATION_FLAG
		};

		enum GLProfileMask {
			GLCoreProfile = SDL_GL_CONTEXT_PROFILE_CORE,
			GLCompatibilityProfile = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
			GLESProfile = SDL_GL_CONTEXT_PROFILE_ES
		};

		StartingConfig();

		std::string  windowTitle;
		unsigned int windowHeight;
		unsigned int windowWidth;
		unsigned int windowFlags;
		unsigned int GLMajor;
		unsigned int GLMinor;
		unsigned int GLRedSize;
		unsigned int GLGreenSize;
		unsigned int GLBlueSize;
		unsigned int GLAlphaSize;
		unsigned int GLBufferSize;
		unsigned int GLDepthSize;
		unsigned int GLStencilSize;
		unsigned int GLAccumRedSize;
		unsigned int GLAccumGreenSize;
		unsigned int GLAccumBlueSize;
		unsigned int GLAccumAlphaSize;
		unsigned int GLMultisampleBuffers;
		unsigned int GLMultisampleSamples;
		unsigned int GLContextFlags;
		GLProfileMask GLProfile;
		bool GLDoubleBuffer;
		bool GLAcceleratedGraphics;
		bool GLStereo;
		bool GLShareContext;
		bool GLRequestSRGB;
		bool mouseGrab;
};

#endif // STARTINGCONFIG_HPP
