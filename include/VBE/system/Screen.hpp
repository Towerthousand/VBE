#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>
#include <vector>

#include <VBE/system/ContextSettings.hpp>

class Screen : public NonCopyable {
	public:
		class DisplayMode {
			public:
				unsigned int getWidth() const {
					return width;
				}

				unsigned int getHeight() const {
					return height;
				}

				vec2u getSize() const  {
					return vec2u(width, height);
				}

				unsigned int getRefreshRate() const {
					return refreshRate;
				}

				unsigned int isFullscreen() const {
					return fullscreen;
				}

				// El usuario no puede crear FullscreenModes, solo puede usar los
				// que le da getFullscreenModes()
				// Si que puede crear windowed modes con el tamanyo que le de la gana.

				// Los windowed modes no tienen refresh rate, usan la del desktop no?
				DisplayMode createWindowedMode(int width, int height) {
					return DisplayMode(width, height, 0, false);
				}
			private:
				DisplayMode(int w, int h, int r, bool f) : width(w), height(h), refreshRate(r), fullscreen(f) {}
				unsigned int width;
				unsigned int height;
				unsigned int refreshRate;
				bool fullscreen;

				friend class Screen;
		};

		static std::vector<DisplayMode> getFullscreenModes();

		// Crear la screen
		Screen(DisplayMode mode, ContextSettings contextSettings = ContextSettings());

		// Cerrar la screen
		~Screen();

		// Run event loop. Must be called every frame.
		void update();

		DisplayMode getDisplayMode() const;
		void setDisplayMode(DisplayMode mode);

		std::string getTitle() const;
		void setTitle(std::string newTitle);

		bool isFocused() const;
		void setPosition(unsigned int x, unsigned int y);

		void swapBuffers() const;
};

#endif // SCREEN_HPP
