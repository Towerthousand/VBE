#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Screen.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

///
/// @brief Handles environment management and I/O devices interaction
///
class Environment {
	public:
		///
		/// @brief Get the current config for the initialization of the Environment
		///
		/// Use this instance of StartingConfig to modify initial
		/// settings for the Environment. Feel free to change it or even replace it
		///
		/// @return The Environment's StartingConfig instance.
		///
		static StartingConfig& config();

		///
		/// @brief Init all of the I/O devices with the provided config
		///
		///	Use this at the start of your application to be able to
		/// access and update the several I/O devices available.
		///
		static void startUp();

		///
		/// @brief Close all of the I/O devices
		///
		///	Use this at the end of your application to clean up
		///
		static void shutDown();

		///
		/// @brief Update all of the I/O devices
		///
		///	Use this every frame to update the I/O devices. This will
		/// process all of the events occurred since the last
		/// update(), or startUp() if this is the first update().
		/// if you don't call update() for a big enough amount of time,
		/// some old events may start to be discarded and in consequence
		/// never processed (which may leave I/O in an invalid state).
		/// This is a really extreme case though.
		///
		/// This function cannot be called on a non-init Environment
		///
		static void update();

		///
		/// @brief Access the current Screen
		///
		/// This function cannot be called on a non-init Environment
		///
		/// @return Valid pointer to a Screen if it was correcty init.
		///         nullptr for an unexisting or non-init screen
		static Screen* getScreen();

		///
		/// @brief Access the current Keyboard
		///
		/// This function cannot be called on a non-init Environment
		///
		/// @return Valid pointer to a Keyboard if it was correcty init.
		///         nullptr for an unexisting or non-init keyboard
		static Keyboard* getKeyboard();

		///
		/// @brief Access the current Screen
		///
		/// This function cannot be called on a non-init Environment
		///
		/// @return Valid pointer to a Mouse if it was correcty init.
		///         nullptr for an unexisting or non-init mouse
		static Mouse* getMouse();

		///
		/// @brief Access the current elapsed time in seconds
		///
		/// This function cannot be called on a non-init Environment
		///
		/// @return Seconds passed since startUp()
		static float getClock();
	private:
		Environment();
		~Environment();

		static bool running;
		static Screen* screen;
		static Keyboard* keyboard;
		static Mouse* mouse;
		static StartingConfig initialConfig;
};

///
/// @class Environment Environment.hpp "environment/Environment.hpp"
///	@ingroup System
///
/// Before starting up the application you can config the Environment
/// variables, specified in @ref StartingConfig. Then just call
/// startUp() to init all the I/O devices and be able to update the input
/// for them each frame with update(). Finally, when your application is done
/// just call shutDown() to close all devices and clean up
///
/// For example, in an application that does not make use of the scenegraph,
/// we would do something like this in our main.cpp:
///
/// @code
/// Environment::config().windowTitle = "MyApp";
/// Environment::config().windowHeight = 1080;
/// Environment::config().windowWidth = 1920;
///
/// //Environment will try to init a window with the specified setup data
/// Environment::startUp();
/// //...execute application
/// while(true) {
///		Environment::update();
///		if(Environment::getKeyboard()->isKeyPressed(Keyboard::A))
///			break;
///		updateLogic();
///		drawStuff();
/// }
/// //Clean up
/// Environment::shutDown();
/// @endcode
///
/// No methods other than config() and startUp() can be used
/// when the Environment hasn't been initiated. Trying to do so will
/// result in an assert failure.
///
/// When init, you can use the getters to get a pointer to the several
/// I/O devices (@ref Screen, @ref Keyboard, @ref Mouse). Beware,
/// the actual pointers MAY be nullptr even when the Environment is init.
/// This will happen when the requested device couldn't be initiated
/// (for example the touch input device when running on a desktop computer).
///
/// Remember that if you are using the Scene Graph for your application, Game
/// will already call startUp() in its constructor, update() in it's update, and
/// shutDown() in its destructor. Do @b not call those yourself when using a Game
/// instance in your application.
///
/// @see StartingConfig, Keyboard, Mouse, Screen, Game
#endif // Environment_HPP
