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
        /// \class DisplayMode Window.hpp <VBE/system/Window.hpp>
        /// \ingroup System
        ///
        /// The DisplayMode class represents a window's format. It can be either Fullscreen or Windowed.
        /// Windowed display modes are arbitrary in size and refresh rate while fullscreen modes are
        /// preset. You can query available fullscreen modes through Window::getFullscreenModes().
        ///
        /// \see Window
        ///

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
        /// \see Window::DisplayMode
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
        /// \see Window::DisplayMode
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
        /// \see Window::DisplayMode
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
        std::string title = "VBE Application";

        static Window* instance;
};
///
/// \class Window Window.hpp <VBE/system/Window.hpp>
/// \ingroup System
///
/// The window holds the OpenGL context where you can draw and display whatever you want. Right now
/// VBE is single-window: __only one window can be instantiated at a time__. The Window::getInstance()
/// function will automatically point to the current window instance if existing and return nullptr otherwise.
///
/// Calling SwapBuffers will swap the back and front OpenGL buffers. In more detail, this will force all
/// driver-postponed draw calls to return (stalling de CPU to wait for the GPU) and then switch the front and back
/// buffers. Understanding this requires basic knowledge of how rendering works: You draw onto an off-screen buffer
/// (the *back* buffer) while another buffer (the *front* buffer) displays some other content. Once every frame,
/// you swap these buffers so that the front buffer always has the latest image. You then proceed to draw the next
/// frame into the back buffer again. You see none of this, it is all done by the driver. Just make sure to call
/// Window::swapBuffers() once per frame.
///
/// When V Sync (wich stands for *vertical sync* is enabled through Window::setVsync() the framerate will behave
/// different than naturally expected. You may be able to loop your game at 120FPS but with V Sync enabled the
/// Window::swapBuffers() function will introduce some waiting in orded to cap your framerate to the display's
/// frequency. If you can only output 60 images (60Hz monitor) per second, your FPS will not go under 16 miliseconds
/// per frame when V Sync is enabled. This eliminates screen tearing and useless CPU/GPU usage.
///
/// You can query wether the user requested a close event (usually through the 'X' window button, or Alt+F4 or something
/// of the sorts) with Window::isClosing(). This just notifies you that the user wants to exit, but will not shut down
/// anything. You can ignore the close event with a call to Window::setClosing(). Window::setClosing() can also be used
/// to invoke close events manually. It is good practice not to ignore user made close events (the user expects the app
/// to end if they ask it to, otherwise it may become frustrating having to kill it through the taks manager/console).
///
/// Note that a system kill event (administrator order to forcefully shut you down) will usually not notify you in any way,
/// so take it into account when handling non-abortable processes (i.e. payment confirmation, disk save modification) and
/// take precautions accordingly.
///

#endif // WINDOW_HPP
