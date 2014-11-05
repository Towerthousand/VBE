#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <vector>

#include <VBE/math.hpp>
#include <VBE/system/ContextSettings.hpp>
#include <VBE/utils/NonCopyable.hpp>
#include <VBE/system/Log.hpp>

class WindowImpl;
///
/// \brief The Window class represents the application's display
///
class Window : public NonCopyable {
	public:

		///
		/// \brief The DisplayMode class represents a display mode that can be used.
		///
		/// There are two types of DisplayModes: Fullscreen and Windowed. You can
		/// create a Windowed mode with the size you want, but you're restricted to
		/// use the Fullscreen modes from Window::getFullscreenModes(), which
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
				/// \brief Returns the width of the DisplayMode.
				/// \return the width of the DisplayMode.
				///
				unsigned int getWidth() const {
					return width;
				}

				///
				/// \brief Returns the height of the DisplayMode.
				/// \return the height of the DisplayMode.
				///
				unsigned int getHeight() const {
					return height;
				}

				///
				/// \brief Returns the size of the DisplayMode.
				/// \return the size of the DisplayMode.
				///
				vec2ui getSize() const  {
					return vec2ui(width, height);
				}

				///
				/// \brief Returns the refresh rate of the DisplayMode.
				///
				/// You may only call this function on Fullscreen modes, since Windowed
				/// modes use the desktop's refresh rate.
				/// \return the refresh rate of the DisplayMode.
				///
				unsigned int getRefreshRate() const {
					VBE_ASSERT(getType() == Windowed, "You may not query the refresh rate of a Windowed mode");
					return refreshRate;
				}

				///
				/// \brief Returns the type of the DisplayMode \see DisplayMode::Type
				/// \return the type of the DisplayMode.
				///
				Type getType() const {
					return type;
				}

				///
				/// \brief Creates a Windowed DisplayMode you can use to create a Window with the size of your choice.
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

				friend class Window;
				friend class WindowImpl;
		};

		///
		/// \brief The VsyncMode enum
		///
		enum VsyncMode {
			DisabledVsync = 0, ///< The framerate won't be capped
			EnabledVsync, ///< The framerate will be capped to the screen's refresh rate
			LateTearingVsync
		};

		///
		/// \brief Returns all the Fullscreen display modes supported by the hardware.
		///
		/// You must use one of these modes to create a Fullscreen Window.
		/// The modes are sorted decreasingly by width, then by height. Therefore,
		/// the first Fullscreen mode is most likely the one you want to use.
		///
		/// \return the supported Fullscreen modes.
		///
		static std::vector<DisplayMode> getFullscreenModes();

		///
		/// \brief Creates a Window with the specified DisplayMode and ContextSettings.
		///
		/// This will create an OpenGL context on the Window so you can draw to it.
		///
		/// It's not guaranteed that the final size of the Window will be the one specified
		/// in the DisplayMode, you should always call getSize to get the real size of the Window.
		/// For example, on Android mode is ignored entirely, and the Window is always
		/// created the size of the Window.
		///
		/// There can be only one Window created at a given time. If there's another Window
		/// already created, this constructor will error.
		///
		/// \param mode DisplayMode to use in the Window
		/// \param contextSettings OpenGL context settings. Optional, if you leave it out it will use
		/// the default settings, which are OpenGL 4.2 on desktop or OpenGL ES 2 on mobile.
		///
		Window(DisplayMode mode, ContextSettings contextSettings = ContextSettings());

		///
		/// \brief Destructor
		///
		~Window();

		///
		/// \brief Runs the event loop, updating the input devices and other events.
		///
		/// You should call it once per frame. Calling it less often will cause the input devices to not update,
		/// and calling it more often will make justPressed/justReleased in the inputs behave wrong.
		///
		/// This method may block on some platforms, such as Android, if the app goes to the background,
		/// to avoid crashes and/or wasting CPU. For this reason, you should call this every frame
		/// even if you're not reading any inputs.
		///
		void update();

		///
		/// \brief Gets the Window size.
		///
		/// This may be different to the size specified in the
		/// DisplayMode, see Window's constructor for details.
		/// \return the Window size.
		///
		vec2ui getSize() const;

		///
		/// \brief Changes the display mode of the Window.
		///
		/// The final Window size may be
		/// different to the one specified in the display mode, see Window constructor for details.
		///
		/// \param mode the new display mode.
		///
		void setDisplayMode(DisplayMode mode);

		///
		/// \brief Changes the Vsync mode of the Window.
		/// \param mode the new vsync mode.
		///
		void setVsync(VsyncMode mode);

		///
		/// \brief Gets the title of the Window.
		/// \return the title.
		///
		std::string getTitle() const;

		///
		/// \brief Sets the title of the Window.
		/// \param newTitle the new title.
		///
		void setTitle(std::string newTitle);

		///
		/// \brief Returns whether the Window is focused.
		///
		/// That is, the Window is in the
		/// foreground and is receiving keyboard and mouse input. It's useful to pause the game
		/// when the user minimizes it, for example.
		///
		/// \return whether the Window is focused.
		///
		bool isFocused() const;

		///
		/// \brief Returns wether the window has been requested to close.
		///
		/// This can happen through a quit event
		/// (alt+F4, system call or similar), a window close or a call to setClosing().
		///
		/// \return whether the Window is closing.
		///
		bool isClosing() const;

		///
		/// \brief Set the closing status of the window.
		///
		/// Setting it won't have any direct effect on the application,
		/// but you can use it to discard user-mode quits. For example, to implement a warning before closing.
		///	Remember that system-mode quits may kill your application anyway.
		///
		/// \param newClosing the new state for the window.
		///
		void setClosing(bool newClosing);

		///
		/// \brief Sets the Window position in pixe.s, relative the the computer Window.
		/// \param x the X coordinate of the position.
		/// \param y the Y coordinate of the position.
		///
		void setPosition(unsigned int x, unsigned int y);

		///
		/// \brief Swaps OpenGL buffers.
		///
		/// This will cause everything you have
		/// drawn using OpenGL to become visible on the Window. You should call this once every
		/// frame after drawing everything.
		///
		void swapBuffers() const;

		///
		/// \brief Returns a pointer to the current Window instance.
		/// \return a pointer to the current created Window, or nullptr if none.
		///
		static Window* getInstance();

	private:
		WindowImpl* impl;
		std::string title;

		static Window* instance;
};

#endif // WINDOW_HPP
