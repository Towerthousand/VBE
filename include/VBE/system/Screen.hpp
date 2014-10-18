#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>
#include <vector>

#include <VBE/math.hpp>
#include <VBE/system/ContextSettings.hpp>
#include <VBE/utils/NonCopyable.hpp>

class ScreenImpl;
class Screen : public NonCopyable {
	public:
		class DisplayMode {
			public:
				enum Type {
					Fullscreen,
					Windowed
				};

				unsigned int getWidth() const {
					return width;
				}

				unsigned int getHeight() const {
					return height;
				}

				vec2ui getSize() const  {
					return vec2ui(width, height);
				}

				unsigned int getRefreshRate() const {
					return refreshRate;
				}

				Type getType() const {
					return type;
				}

				// El usuario no puede crear FullscreenModes, solo puede usar los
				// que le da getFullscreenModes()
				// Si que puede crear windowed modes con el tamanyo que le de la gana.

				// Los windowed modes no tienen refresh rate, usan la del desktop no?
				static DisplayMode createWindowedMode(int width, int height) {
					return DisplayMode(width, height, 0, Windowed);
				}
			private:
				DisplayMode(int w, int h, int r, Type t) : width(w), height(h), refreshRate(r), type(t) {}
				unsigned int width;
				unsigned int height;
				unsigned int refreshRate;
				Type type;

				// Implementation defined, do not use.
				int implementationData;

				friend class Screen;
				friend class ScreenImpl;
		};

		static std::vector<DisplayMode> getFullscreenModes();

		// Crear la screen
		Screen(DisplayMode mode, ContextSettings contextSettings = ContextSettings());

		// Cerrar la screen
		~Screen();

		// Run event loop. Must be called every frame.
		void update();

		vec2ui getSize() const;
		void setDisplayMode(DisplayMode mode);

		std::string getTitle() const;
		void setTitle(std::string newTitle);

		bool isFocused() const;
		void setPosition(unsigned int x, unsigned int y);

		void swapBuffers() const;

		// Returns a pointer to the Screen instance.
		static Screen* getInstance();

	private:
		ScreenImpl* impl;
		std::string title;

		static Screen* instance;

};

#endif // SCREEN_HPP
