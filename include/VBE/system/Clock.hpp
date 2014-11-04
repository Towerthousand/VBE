#ifndef CLOCK_HPP
#define CLOCK_HPP

///
/// \brief The Clock class represents the application's internal clock.
///
class Clock {
	public:

		///
		/// \brief getSeconds Gets the value of the clock in seconds.
		/// The returned value increases by 1 every second. The origin
		/// of the clock (the moment when it has the value 0) is unspecified.
		///
		static float getSeconds();

		///
		/// \brief sleepSeconds Sleeps for the specified amount of seconds.
		/// \param seconds The number of seconds to sleep
		///
		static void sleepSeconds(float seconds);
};

#endif // CLOCK_HPP
