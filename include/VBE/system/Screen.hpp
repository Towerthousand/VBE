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

		///
		/// \brief The DisplayMode class represents a display mode that can be used.
		/// There are two types of DisplayModes: Fullscreen and Windowed. You can
		/// create a Windowed mode with the size you want, but you're restricted to
		/// use the Fullscreen modes from Screen::getFullscreenModes(), which
		/// are the modes supported by the hardware.
		///
		class DisplayMode {
			public:

				///
				/// \brief Types of DisplayModes
				///
				enum Type {
					Fullscreen,
					Windowed
				};

				///
				/// \brief getWidth returns the width of the DisplayMode.
				/// \return the width of the DisplayMode.
				///
				unsigned int getWidth() const {
					return width;
				}

				///
				/// \brief getHeight returns the height of the DisplayMode.
				/// \return the height of the DisplayMode.
				///
				unsigned int getHeight() const {
					return height;
				}

				///
				/// \brief getSize returns the size of the DisplayMode.
				/// \return the size of the DisplayMode.
				///
				vec2ui getSize() const  {
					return vec2ui(width, height);
				}

				///
				/// \brief getRefreshRate returns the refresh rate of the DisplayMode.
				/// You may only call this function on Fullscreen modes, since Windowed
				/// modes use the desktop's refresh rate.
				/// \return the refresh rate of the DisplayMode.
				///
				unsigned int getRefreshRate() const {
					VBE_ASSERT(getType() == Windowed, "You may not query the refresh rate of a Windowed mode");
					return refreshRate;
				}

				///
				/// \brief getType Returns the type of the DisplayMode: Fullscreen or Windowed.
				/// \return the type of the DisplayMode.
				///
				Type getType() const {
					return type;
				}

				///
				/// \brief createWindowedMode Creates a Windowed DisplayMode you can use to
				/// create a Screen with the size of your choice.
				/// \param width the width of the window.
				/// \param height the height of the window.
				/// \return the created windowed mode.
				///
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

		///
		/// \brief getFullscreenModes returns all the fullscreen display modes supported by
		/// the hardware. You must use one of these modes to create a fullscreen Screen.
		/// The modes are sorted decreasingly by width, then by height. Therefore,
		/// the first fullscreen mode is most likely the one you want to use.
		/// \return the supported fullscreen modes.
		///
		static std::vector<DisplayMode> getFullscreenModes();

		///
		/// \brief Screen Creates a screen with the specified DisplayMode and ContextSettings.
		/// This will create an OpenGL context on the screen so you can draw to it.
		///
		/// It's not guaranteed that the final size of the Screen will be the one specified
		/// in the DisplayMode, you should always call getSize to get the real size of the screen.
		/// For example, on Android mode is ignored entirely, and the screen is always
		/// created the size of the screen.
		///
		/// There can be only one Screen created at a given time. If there's another screen
		/// already created, this constructor will error.
		///
		/// \param mode DisplayMode to use in the Screen
		/// \param contextSettings OpenGL context settings. Optional, if you leave it out it will use
		/// the default settings, which are OpenGL 4.2 on desktop or OpenGL ES 2 on mobile.
		///
		Screen(DisplayMode mode, ContextSettings contextSettings = ContextSettings());

		~Screen();

		///
		/// \brief update runs the event loop, updating the input devices and other events. You
		/// should call it once per frame. Calling it less often will cause the input devices to not update,
		/// and calling it more often will make justPressed/justReleased in the inputs behave wrong.
		///
		/// This method may block on some platforms, such as Android, if the app goes to the background,
		/// to avoid crashes and/or wasting CPU. For this reason, you should call this every frame
		/// even if you're not reading any inputs.
		///
		void update();

		///
		/// \brief getSize gets the screen size. This may be different to the size specified in the
		/// DisplayMode, see Screen's constructor for details.
		/// \return the screen size.
		///
		vec2ui getSize() const;

		///
		/// \brief setDisplayMode changes the display mode of the screen. The final screen size may be
		/// different to the one specified in the display mode, see Screen's constructor for details.
		/// \param mode the new display mode.
		///
		void setDisplayMode(DisplayMode mode);

		///
		/// \brief getTitle gets the title of the Screen.
		/// \return the title.
		///
		std::string getTitle() const;

		///
		/// \brief setTitle sets the title of the Screen.
		/// \param newTitle the new title.
		///
		void setTitle(std::string newTitle);

		///
		/// \brief isFocused returns whether the Screen is focused, that is, the screen is in
		/// foreground and is receiving keyboard and mouse input. It's useful to pause the game
		/// when the user minimizes it, for example.
		/// \return whether the Screen is focused.
		///
		bool isFocused() const;

		///
		/// \brief setPosition Sets the Screen position in pixe.s, relative the the computer screen.
		/// \param x the X coordinate of the position.
		/// \param y the Y coordinate of the position.
		///
		void setPosition(unsigned int x, unsigned int y);

		///
		/// \brief swapBuffers Swaps OpenGL buffers. This will cause everything you have
		/// drawn using OpenGL to become visible on the Screen. You should call this once every
		/// frame after drawing everything.
		///
		void swapBuffers() const;

		///
		/// \brief getInstance returns a pointer to the current Screen instance.
		/// \return a pointer to the current created Screen, or nullptr if none.
		///
		static Screen* getInstance();

	private:
		ScreenImpl* impl;
		std::string title;

		static Screen* instance;

};

#endif // SCREEN_HPP
