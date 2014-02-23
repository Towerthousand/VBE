#ifndef SCREEN_HPP
#define SCREEN_HPP
#include "tools.hpp"

class Screen {
	public:
		struct DisplayMode {
				DisplayMode(int h, int w, int r) : height(h), width(w), refreshRate(r) {}
				unsigned int height;
				unsigned int width;
				unsigned int refreshRate;
		};

		enum WindowFlags {
			WINDOW_FULLSCREEN = SDL_WINDOW_FULLSCREEN, //fullscreen window
			WINDOW_FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP, //fullscreen window at the current desktop resolution
			WINDOW_OPENGL = SDL_WINDOW_OPENGL, //window usable with OpenGL context
			WINDOW_SHOWN = SDL_WINDOW_SHOWN, //window is visible
			WINDOW_HIDDEN = SDL_WINDOW_HIDDEN, //window is not visible
			WINDOW_BORDERLESS = SDL_WINDOW_BORDERLESS, //no window decoration
			WINDOW_RESIZABLE = SDL_WINDOW_RESIZABLE, //window can be resized
			WINDOW_MINIMIZED = SDL_WINDOW_MINIMIZED, //window is minimized
			WINDOW_MAXIMIZED = SDL_WINDOW_MAXIMIZED, //window is maximized
			WINDOW_INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED, //window has grabbed input focus
			WINDOW_INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS, //window has input focus
			WINDOW_MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS //window has mouse focus
		};

		Screen();
		~Screen();

		void initWindow(std::string name, unsigned int width, unsigned int height, unsigned long int flags);
		void resize(unsigned int newWidth, unsigned int newHeight);
		void setDisplayMode(unsigned int displayMode, unsigned int displayIndex);
		void goFullscreen(unsigned int displayMode = 0, unsigned int displayIndex = 0);
		void goWindowed(unsigned int newWidth, unsigned int newHeight);
		void swapBuffers() const;
		void setTitle(std::string newTitle);
		void setPosition(unsigned int x, unsigned int y);
		void setGrab(bool grab);
		void setBorder(bool border);

		unsigned int getDisplayCount() const;
		std::vector<DisplayMode> getDisplayModes(unsigned int displayIndex = 0) const;
		DisplayMode getCurrentDisplayMode(int displayIndex = 0) const;
		bool isWindowInit() const { return (window != nullptr); }
		unsigned int getHeight() const { return height; }
		unsigned int getWidth() const { return width; }
		vec2ui getSize() const { return vec2ui(width,height); }
		std::string getTitle() const;

	private:
		SDL_Window* window;
		SDL_GLContext context;
		int height;
		int width;
		bool fullscreen;

		friend class Enviorment;
};

#endif // SCREEN_HPP
