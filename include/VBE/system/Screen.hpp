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

				unsigned int isWindowed() const {
					return windowed;
				}
			private:
				DisplayMode(int w, int h, int r) : width(w), height(h), refreshRate(r) {}
				unsigned int width;
				unsigned int height;
				unsigned int refreshRate;
				bool windowed;

				friend class Screen;
		};

		static std::vector<DisplayMode> getFullscreenModes(unsigned int displayIndex = 0);

		// Crear la screen
		Screen(DisplayMode mode, ContextSettings contextSettings = ContextSettings());

		// Cerrar la screen
		~Screen();

		void resize(unsigned int newWidth, unsigned int newHeight);
		void setDisplayMode(unsigned int displayMode = 0, unsigned int displayIndex = 0);
		void setDesktopDisplayMode();
		void goFullscreen(unsigned int displayMode = 0, unsigned int displayIndex = 0);
		void goWindowed(unsigned int newWidth, unsigned int newHeight);
		void swapBuffers() const;
		void setTitle(std::string newTitle);
		void setPosition(unsigned int x, unsigned int y);
		void setBorder(bool border);

		unsigned int getDisplayCount() const;
		DisplayMode getCurrentDisplayMode(int displayIndex = 0) const;
		bool isWindowInit() const { return (window != nullptr); }
		unsigned int getHeight() const { return height; }
		unsigned int getWidth() const { return width; }
		vec2ui getSize() const { return vec2ui(width,height); }
		std::string getTitle() const;
		bool isFocused() const { return focused; }
};

#endif // SCREEN_HPP
