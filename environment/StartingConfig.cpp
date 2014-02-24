#include "StartingConfig.hpp"
#include "Screen.hpp"

StartingConfig::StartingConfig() :
	windowTitle("VBE_APP"),
	windowHeight(0),
	windowWidth(0),
	windowFlags(Screen::WINDOW_OPENGL|Screen::WINDOW_SHOWN),
	GLMajor(4),
	GLMinor(2),
	GLRedSize(3),
	GLGreenSize(3),
	GLBlueSize(2),
	GLAlphaSize(0),
	GLBufferSize(0),
	GLDepthSize(16),
	GLStencilSize(0),
	GLAccumRedSize(0),
	GLAccumGreenSize(0),
	GLAccumBlueSize(0),
	GLAccumAlphaSize(0),
	GLMultisampleBuffers(0),
	GLMultisampleSamples(0),
	GLContextFlags(0),
	GLProfile(GLCoreProfile),
	GLDoubleBuffer(true),
	GLAcceleratedGraphics(true),
	GLStereo(false),
	GLShareContext(false),
	GLRequestSRGB(false),
	mouseGrab(false)
{}
