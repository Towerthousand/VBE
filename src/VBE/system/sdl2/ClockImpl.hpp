#ifndef CLOCKIMPL_HPP
#define CLOCKIMPL_HPP

class ClockImpl
{
    public:
        static long long getMicroseconds();
        static void sleepMicroseconds(long long useconds);
};

#endif // CLOCKIMPL_HPP
