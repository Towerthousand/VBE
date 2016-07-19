#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <VBE/config.hpp>
#include <VBE/math.hpp> // vec3, vec4, ivec4, mat4 (core)

//VBE_ASSERT
#ifdef VBE_DEBUG
#ifdef MSC_VER
#define VBE_ASSERT(expression, string) do \
{ \
    if(!(expression)) { \
    Log::error() << "ASSERT FAILED, STOPPING " << Log::Line;\
    Log::error() << "Reason: " << string << Log::Line; \
    Log::error() << "At file " << __FILE__ << " inside function " << __FUNCSIG__ << " on line " << __LINE__ << Log::Flush; \
    std::cout << Log::getContents() << std::endl; \
    assert(expression); \
    std::exit(-1); \
    } \
    } while (0)
#define VBE_SIMPLE_ASSERT(expression) do \
{ \
    if(!(expression)) { \
    Log::error() << "ASSERT FAILED, STOPPING " << Log::Line;\
    Log::error() << "At file " << __FILE__ << " inside function " << __FUNCSIG__ << " on line " << __LINE__ << Log::Flush; \
    std::cout << Log::getContents() << std::endl; \
    assert(expression); \
    std::exit(-1); \
    } \
    } while (0)
#else
#define VBE_ASSERT(expression, string) do \
{ \
    if(!(expression)) { \
    Log::error() << "ASSERT FAILED, STOPPING " << Log::Line;\
    Log::error() << "Reason: " << string << Log::Line; \
    Log::error() << "At file " << __FILE__ \
    << " inside function " << __PRETTY_FUNCTION__ << " on line " << __LINE__ << Log::Flush; \
    assert(expression); \
    std::exit(-1); \
    } \
    } while (0)
#define VBE_ASSERT_SIMPLE(expression) do \
{ \
    if(!(expression)) { \
    Log::error() << "ASSERT FAILED, STOPPING " << Log::Line;\
    Log::error() << "At file " << __FILE__ \
    << " inside function " << __PRETTY_FUNCTION__ << " on line " << __LINE__ << Log::Flush; \
    assert(expression); \
    std::exit(-1); \
    } \
    } while (0)
#endif
#else
#define VBE_ASSERT(expression , string) {}
#define VBE_ASSERT_SIMPLE(expression) {}
#endif

//GL_ASSERT
#ifdef VBE_DEBUG
#define GL_ASSERT( gl_code ) do \
{ \
    gl_code; \
    GLenum __gl_error_code = glGetError(); \
    VBE_ASSERT(__gl_error_code == GL_NO_ERROR, "OpenGL Error with id: 0x" << std::hex << __gl_error_code << std::dec); \
    } while(0)
#else
#define GL_ASSERT( gl_code ) gl_code
#endif

//VBE_WARNING
#ifdef VBE_DEBUG
#ifdef MSC_VER
#define VBE_WARN(expression , string) do \
{ \
    if(!(expression)) { \
    Log::warning() << "Warning Condition Failed " << Log::Line;\
    Log::warning() << "Message: " << string << Log::Line; \
    Log::warning() << "At file " << __FILE__ << \
    " inside function " << __FUNCSIG__ << " on line " << __LINE__ << Log::Flush; \
    } \
    } while (0)
#else
#define VBE_WARN(expression , string) do \
{ \
    if(!(expression)) { \
    Log::warning() << "Warning Condition Failed " << Log::Line;\
    Log::warning() << "Message: " << string << Log::Line; \
    Log::warning() << "At file " << __FILE__ << \
    " inside function " << __PRETTY_FUNCTION__ << " on line " << __LINE__ << Log::Flush; \
    } \
    } while (0)
#endif
#else
#define VBE_WARN(expression , string) {}
#endif

//VBE_LOG,_DLOG
#ifdef VBE_DEBUG
#define VBE_LOG(msg) Log::message() << msg << Log::Flush
#else
#define VBE_LOG(msg) {}
#endif
#ifdef VBE_DETAIL
#define VBE_DLOG(msg) VBE_LOG(msg)
#else
#define VBE_DLOG(msg) {}
#endif

///
/// \brief The Log class lets you log things with ease from anywhere
///
class Log {
    private:
        enum LogType {
            Message = 0,
            Warning,
            Error
        };

        Log(LogType t) : type(t) {}
        ~Log() {}

        static void save() {
            std::ofstream file(outPath,std::ofstream::out|std::ofstream::trunc);
            file << endFile.str();
            file.close();
        }

        const LogType type;
        mutable std::ostringstream msg;

        static Log* messageInstance;
        static Log* warningInstance;
        static Log* errorInstance;
        static std::ostringstream endFile;
        static unsigned char flags;
        static std::string outPath;

    public:
        ///
        /// \brief The LogModifiers enum
        ///
        enum LogModifiers {
            Flush = 0, ///< Flush the stream and save if appropiate
            Line ///< Insert indented line jump into current message
        };

        ///
        /// \brief The LogFlags enum lists all the flags that can be specified on Log::setFlags()
        ///
        enum LogFlags {
            Timestamp	= 0x01, ///< Will print a timestamp (HH:MM:SS) into each log entry
            StandardOut = 0x02, ///< Every Log::Flush will write the current entry to the standard out channel
#ifndef VBE_SYSTEM_ANDROID
            AlwaysSave = 0x04, ///< Every Log::Flush will save the whole log report to the path specified
            ///< by Log::setFilePath(). Only on desktop.
#endif
            GMTime = 0x08 ///< The timestamps will be on GM time.
        };

        ///
        /// \brief Default << operator. Will redirect to an internal std::ostringstream.
        ///
        template<class T> const Log& operator<<(const T& t) const {
            msg << t;
            return *this;
        }

        ///
        /// \brief Set the log flags. Must be a OR'd collection of Log::LogFlags \see LogFlags.
        ///
        static void setFlags(unsigned char f) {
            flags = f;
        }

        ///
        /// \brief Use this logging function to log normal messages.
        ///
        static Log& message() {
            if(messageInstance == nullptr)
                messageInstance = new Log(Message);
            return *messageInstance;
        }

        ///
        /// \brief Use this logging function to log warning messages.
        ///
        static Log& warning() {
            if(warningInstance == nullptr)
                warningInstance = new Log(Warning);
            return *warningInstance;
        }

        ///
        /// \brief Use this logging function to log error messages.
        ///
        static Log& error() {
            if(errorInstance == nullptr)
                errorInstance = new Log(Error);
            return *errorInstance;
        }

        ///
        /// \brief Get the contents of the log report.
        ///
        /// \return A string with all messages since the application's startup.
        ///
        static std::string getContents() { return endFile.str(); }
#ifndef VBE_SYSTEM_ANDROID
        ///
        /// \brief setFilePath Change the out path of the log.
        ///
        /// The default out path is "log.txt". On mobile, the saving functionality is disabled, since the
        /// "AlwaysSave" flag is not defined.
        ///
        /// \param newPath The path where to save from now on
        ///
        static void setFilePath(std::string newPath) { outPath = newPath; }
#endif
};
///
/// \class Log Log.hpp <VBE/system/Log.hpp>
///	\ingroup System
///
/// You can use this class to emit messages/warnings/errors at any time, from anywhere. Example:
/// ~~~{.cpp}
/// Log::message() << "Hi, my name is Bud and I'm " << 20 << "years old." << Log::Line << "this is another line. The stream won't be flushed untill you tell << Log::Line << it to do so, like so: << Log::Flush;
/// ~~~
///
/// You can implement your own override for the << operator to log custom classes. For example, this header
/// defines several generic GLM overrides for the operator like so:
/// ~~~{.cpp}
/// template<class T>
/// const Log& operator<<(const Log& log, const glm::tvec4<T>& v) {
///		log << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
///		return log;
/// }
/// ~~~
/// For example, for any class `MyClass` you would:
/// ~~~{.cpp}
/// const Log& operator<<(const Log& log, const MyClass& v) {
///		log << "LogOfMyClass!: " << MyClass.myInt1 << " " << MyClass.myString1;
///		return log;
/// }
/// ~~~
/// Note that this header also defines several macros used internally (feel free to use them too):
///
/// `VBE_LOG(Message)` will just encapsulate the message between a Log::message() and Log::Flush.
///
/// `VBE_DLOG(Message)` will do the same as `VBE_LOG`.
///
/// `VBE_ASSERT(expression, Message)` will assert the expression. If it fails, the string will be
/// logged as an error and the application will exit(-1).
///
/// `GL_ASSERT(gl_code)` will execute the gl instruction 'gl_code' and then check for openGL internal errors.
///
/// The catch: if `VBE_DEBUG` is not defined, `VBE_LOG` and `VBE_ASSERT` won't do anything and `GL_ASSERT` will
/// not check for errors. This is done in order to not stall an (ideally) bug-free release build. Additionally,
/// VBE_DLOG will do the same as VBE_LOG only if `VBE_DETAIL` is defined.
///
/// By default, `VBE_DEBUG` will only be defined in environments where `NDEBUG` (the standard debug flag) is defined.
/// `VBE_DETAIL` is never defined by VBE, define it manually if you want VBE to log everything it does. It may flood
/// your log report.
///

//Template specialitzations that use private stuff. Implemented in cpp (no actual templating going on)
template<> const Log& Log::operator<< (const Log::LogModifiers& t) const;

//Templated, non-member operator overloaders that must be implemented where declared (templates suck at linking)
//User can define them wherever they want for their own objects.
template<class T>
const Log&operator << (const Log& log, const glm::tvec4<T>& v) {
    log << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return log;
}

template<class T>
const Log&operator << (const Log& log, const glm::tvec3<T>& v) {
    log << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return log;
}

template<class T>
const Log&operator << (const Log& log, const glm::tvec2<T>& v) {
    log << "vec2(" << v.x << ", " << v.y << ")";
    return log;
}

template<class T>
const Log&operator << (const Log& log, const glm::tmat3x3<T>& m) {
    for(unsigned int i = 0; i < 3; ++i) {
        for(unsigned int j = 0; j < 3; ++j) {
            log << m[j][i];
            if(j < 2) log << " ";
        }
        if(i < 2) log << Log::Line;
    }
    return log;
}

template<class T>
const Log&operator << (const Log& log, const glm::tmat4x4<T>& m) {
    for(unsigned int i = 0; i < 4; ++i) {
        for(unsigned int j = 0; j < 4; ++j) {
            log << m[j][i];
            if(j < 3) log << " ";
        }
        if(i < 3) log << Log::Line;
    }
    return log;
}

template<class T>
const Log&operator << (const Log& log, const std::vector<T>& v) {
    for(unsigned int i = 0; i < v.size(); ++i) {
        log << v[i];
        if(i != v.size()-1) log << " ";
    }
    return log;
}

#endif // LOG_HPP
