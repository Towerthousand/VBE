#ifndef CLOCK_HPP
#define CLOCK_HPP

///
/// \brief The Clock class represents the application's internal clock.
///
class Clock {
    public:

        ///
        /// \brief Gets the value of the clock in seconds.
        /// The returned value increases by 1 every second. The origin
        /// of the clock (the moment when it has the value 0) is unspecified.
        ///
        static float getSeconds();
        static long long getMicroseconds();

        ///
        /// \brief Sleeps for the specified amount of seconds.
        /// \param seconds The number of seconds to sleep
        ///
        static void sleepSeconds(float seconds);
        static void sleepMicroseconds(long long useconds);
};
///
/// \class Clock Clock.hpp <VBE/system/Clock.hpp>
///	\ingroup System
///
/// With this class you can query the elapsed time since the application started
/// and a you can also sleep the current thread for any amount of time.
///

#endif // CLOCK_HPP
