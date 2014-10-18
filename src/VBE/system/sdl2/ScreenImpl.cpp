#include <VBE/system/sdl2/ScreenImpl.hpp>
#include <VBE/system/sdl2/InputImpl.hpp>
#include <VBE/system/Log.hpp>

// static
bool ScreenImpl::isSDLInit = false;
SDL_Window* ScreenImpl::window;
SDL_GLContext ScreenImpl::context;
bool ScreenImpl::focused = false;

//static
void ScreenImpl::initSDL() {
	if(isSDLInit) return;
	VBE_ASSERT(SDL_WasInit(SDL_INIT_EVERYTHING) == 0, "SDL Has been init from outside of this application");
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	VBE_ASSERT(ret == 0, "Error when initializating SDL: " << SDL_GetError());
	isSDLInit = true;
}

// static
std::vector<Screen::DisplayMode> ScreenImpl::getFullscreenModes() {
	initSDL();

	// We have no multiple screen support in VBE for now, we just
	// use the main screen.
	const int displayIndex = 0;

	std::vector<Screen::DisplayMode> v;
	int numModes = SDL_GetNumDisplayModes(displayIndex);
	for(int i = 0; i < numModes; ++i) {
		SDL_DisplayMode mode;
		SDL_ASSERT(SDL_GetDisplayMode(displayIndex, i, &mode));

		Screen::DisplayMode dm(mode.w, mode.h, mode.refresh_rate, Screen::DisplayMode::Fullscreen);

		// Save the SDL displaymode index so we can
		// recover the displaymode later.
		dm.implementationData = i;
		v.push_back(dm);
	}
	return v;
}

// static
vec2ui ScreenImpl::getSize() {
	int x, y;
	SDL_GetWindowSize(window, &x, &y);
	return vec2ui(x, y);
}

// static
void ScreenImpl::create(Screen::DisplayMode mode, ContextSettings config) {
	initSDL();
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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, config.versionMajor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, config.versionMinor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, config.contextFlags);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, config.profile);
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, config.shareContext);
	SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, config.requestSRGB);

	// Create the window, but not show it yet because we need to set the display mode
	// if the window is fullscreen.
	window = SDL_CreateWindow("VBE Game",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  mode.getWidth(), mode.getHeight(),
							  SDL_WINDOW_OPENGL);
	VBE_ASSERT(window != nullptr, "Failed to init window: "<<SDL_GetError());

	if(mode.getType() == Screen::DisplayMode::Fullscreen) {
		// We have no multiple screen support in VBE for now, we just
		// use the main screen.
		const int displayIndex = 0;

		// Recover the SDL DisplayMode from the VBE DisplayMode
		SDL_DisplayMode sdlMode;
		SDL_ASSERT(SDL_GetDisplayMode(displayIndex, mode.implementationData, &sdlMode));

		SDL_ASSERT(SDL_SetWindowDisplayMode(window, &sdlMode));
		SDL_ASSERT(SDL_SetWindowFullscreen(window, SDL_TRUE));
	}

	// Create the GL context
	context = SDL_GL_CreateContext(window);
	VBE_ASSERT(context != nullptr, "Failed to create OpenGL context: "<<SDL_GetError());

	// Finally show the window.
	SDL_ShowWindow(window);

	// Init input
	InputImpl::init();
}

// static
void ScreenImpl::destroy() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

// static
void ScreenImpl::setDisplayMode(Screen::DisplayMode mode) {
	if(mode.getType() == Screen::DisplayMode::Fullscreen) {
		// We have no multiple screen support in VBE for now, we just
		// use the main screen.
		const int displayIndex = 0;

		// Recover the SDL DisplayMode from the VBE DisplayMode
		SDL_DisplayMode sdlMode;
		SDL_ASSERT(SDL_GetDisplayMode(displayIndex, mode.implementationData, &sdlMode));

		SDL_ASSERT(SDL_SetWindowDisplayMode(window, &sdlMode));
		SDL_ASSERT(SDL_SetWindowFullscreen(window, SDL_TRUE));
	}
	else { // Windowed
		SDL_ASSERT(SDL_SetWindowFullscreen(window, SDL_FALSE));
		SDL_SetWindowSize(window, mode.getWidth(), mode.getHeight());
	}
}

// static
void ScreenImpl::update() {
	InputImpl::update();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {

			// System events
			case SDL_QUIT:
				// TODO: Exit properly
				exit(1);

				// We don't want to force users to use Game.
				// Game should check if the screen has closed, not otherwise.
				// TODO fix
				//if(Game::i() != nullptr)
				//	Game::i()->isRunning = false;
				break;

				// Window events
			case SDL_WINDOWEVENT:
				processEvent(e);
				break;

			// Keyboard events
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_TEXTEDITING:
			case SDL_TEXTINPUT:
			// Mouse events
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
			// TODO Touch events
				InputImpl::processEvent(e);
				break;
			default:
				break;
		}
	}
}


void ScreenImpl::processEvent(const SDL_Event &e) {
	switch(e.window.type) {
		case SDL_WINDOWEVENT_CLOSE:
			//TODO FIX THIS
			//if(Game::i() != nullptr)
			//	Game::i()->isRunning = false;
			break;
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


// static
void ScreenImpl::setTitle(std::string newTitle) {
	SDL_SetWindowTitle(window, newTitle.c_str());
}

// static
bool ScreenImpl::isFocused() {
	return focused;
}

// static
void ScreenImpl::setPosition(unsigned int x, unsigned int y) {
//	VBE_ASSERT(!fullscreen, "Window must not be fullscreen to call setPosition");
	SDL_SetWindowPosition(window, x, y);
}

// static
void ScreenImpl::swapBuffers() {
	SDL_GL_SwapWindow(window);
}
