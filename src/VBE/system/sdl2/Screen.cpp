#include "Screen.hpp"
#include "../scene/Game.hpp"
#include <SDL2/SDL.h>


int contextFlagsToSdl(ContextFlags f) {
	int r = 0;
	if(f & DebugContext) r |= SDL__CONTEXT_DEBUG_FLAG;
	if(f & ForwardCompatibleContext) r |= SDL__CONTEXT_FORWARD_COMPATIBLE_FLAG;
	if(f & RobustAccessContext) r |= SDL__CONTEXT_ROBUST_ACCESS_FLAG;
	if(f & RobustIsolationContext) r |= SDL__CONTEXT_RESET_ISOLATION_FLAG;
	return r;
}

int profileMaskToSdl(ProfileMask f) {
	int r = 0;
	if(f & CoreProfile) r |= SDL__CONTEXT_PROFILE_CORE;
	if(f & CompatibilityProfile) r |= SDL__CONTEXT_PROFILE_COMPATIBILITY;
	if(f & ESProfile) r |= SDL__CONTEXT_PROFILE_ES;
	return r;
}

Screen::Screen(StartingConfig config) : window(nullptr), height(config.windowHeight), width(config.windowWidth), fullscreen((config.windowFlags&WINDOW_FULLSCREEN) == 0), focused(true) {
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, config.redBits);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, config.greenBits);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, config.blueBits);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, config.alphaBits);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, config.bufferBits);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, config.doubleBuffer);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, config.depthBits);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, config.stencilBits);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, config.accumRedBits);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, config.accumGreenBits);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, config.accumBlueBits);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, config.accumAlphaBits);
	SDL_GL_SetAttribute(SDL_GL_STEREO, config.stereo);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, config.multisampleBuffers);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, config.multisampleSamples);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, config.acceleratedGraphics);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, config.major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, config.minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, config.contextFlags);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, config.profile);
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, config.shareContext);
	SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, config.requestSRGB);

	window = SDL_CreateWindow(config.windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, config.windowFlags);
	VBE_ASSERT(window != nullptr, "Failed to init window: "<<SDL_GetError());
	context = SDL_GL_CreateContext(window);
	VBE_ASSERT(context != nullptr, "Failed to create OpenGL context"<<SDL_GetError());

	fullscreen = ((config.windowFlags&Screen::WINDOW_FULLSCREEN) != 0 || (config.windowFlags&Screen::WINDOW_FULLSCREEN_DESKTOP));
	if(fullscreen)
		setDisplayMode();
}

Screen::~Screen() {
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_GL_DeleteContext(context);
}

void Screen::processEvent(const SDL_Event &e) {
	switch(e.window.type) {
		case SDL_WINDOWEVENT_CLOSE:
			//TODO FIX THIS
			if(Game::i() != nullptr)
				Game::i()->isRunning = false;
			break;
		case SDL_WINDOWEVENT_RESIZED:
			updateSize();
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			updateSize();
			break;
		case SDL_WINDOWEVENT_ENTER:
			focused = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			focused = false;
			break;
		case SDL_WINDOWEVENT_EXPOSED: break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			focused = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			focused = false;
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			focused = false;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED: break;
		case SDL_WINDOWEVENT_MINIMIZED: break;
		case SDL_WINDOWEVENT_MOVED: break;
		case SDL_WINDOWEVENT_RESTORED: break;
		case SDL_WINDOWEVENT_SHOWN:
			focused = true;
			break;
		default: break;
	}
}

void Screen::updateSize() {
	SDL_GetWindowSize(window, &this->width, &this->height);
}

void Screen::goFullscreen(unsigned int displayMode, unsigned int displayIndex) {
	VBE_WARN(!fullscreen, "Going fullscreen on an already fullscreen window");
	SDL_SetWindowFullscreen(window,WINDOW_FULLSCREEN);
	fullscreen = true;
	setDisplayMode(displayMode, displayIndex);
}

void Screen::goWindowed(unsigned int newWidth, unsigned int newHeight) {
	VBE_WARN(fullscreen, "Going windowed on an already windowed window");
	SDL_SetWindowFullscreen(window,0);
	fullscreen = false;
	resize(newWidth,newHeight);
}

void Screen::swapBuffers() const {
	SDL_GL_SwapWindow(window);
}

void Screen::setTitle(std::string newTitle) {
	SDL_SetWindowTitle(window, newTitle.c_str());
}

void Screen::setDisplayMode(unsigned int displayMode, unsigned int displayIndex) {
	VBE_ASSERT(fullscreen, "Trying to set a display mode for a non-fullscreen window" << Log::Line
			   << "Display modes are only for fullscreen windows" << Log::Line
			   << "To set the size of a non-fullscreen window use resize()");
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, displayMode, &mode);
	SDL_SetWindowDisplayMode(window,&mode);
	SDL_HideWindow(window);
	SDL_ShowWindow(window);
	SDL_RaiseWindow(window);
	updateSize();
}

void Screen::setDesktopDisplayMode() {
	VBE_ASSERT(fullscreen, "Trying to set a display mode for a non-fullscreen window" << Log::Line
			   << "Display modes are only for fullscreen windows" << Log::Line
			   << "To set the size of a non-fullscreen window use resize()");
	SDL_SetWindowDisplayMode(window,nullptr);
	updateSize();
}

void Screen::resize(unsigned int newWidth, unsigned int newHeight) {
	VBE_ASSERT(!fullscreen, "Trying to resize a fullscreen window" << Log::Line
			   << "Resizing is only for fullscreen windows" << Log::Line
			   << "To set the display mode of a fullscreen window use setDisplayMode()");
	SDL_SetWindowSize(window, newWidth, newHeight);
	updateSize();
}

void Screen::setPosition(unsigned int x, unsigned int y) {
	VBE_ASSERT(!fullscreen, "Window must not be fullscreen to call setPosition");
	SDL_SetWindowPosition(window, x, y);
}

void Screen::setBorder(bool border) {
	SDL_SetWindowBordered(window, (border? SDL_TRUE : SDL_FALSE));
}

unsigned int Screen::getDisplayCount() const {
	return SDL_GetNumVideoDisplays();
}

std::vector<Screen::DisplayMode> Screen::getDisplayModes(unsigned int displayIndex) {
	std::vector<DisplayMode> v;
	int numModes = SDL_GetNumDisplayModes(displayIndex);
	for(int i = 0; i < numModes; ++i) {
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(displayIndex, i, &mode);
		v.push_back(DisplayMode(mode.h, mode.w, mode.refresh_rate));
	}
	return v;
}

Screen::DisplayMode Screen::getCurrentDisplayMode(int displayIndex) const {
	VBE_ASSERT(fullscreen, "Cannot get current display mode of non-fullscreen window" << Log::Line
			   << "Display modes are for fullscreens windows only" << Log::Line
			   << "To get the size of a non-fullscreen window use Screen::getSize()");
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(displayIndex, &mode);
	return DisplayMode(mode.h, mode.w, mode.refresh_rate);
}

std::string Screen::getTitle() const {
	return std::string(SDL_GetWindowTitle(window));
}
