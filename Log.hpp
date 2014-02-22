#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "glm/glm.hpp" // vec3, vec4, ivec4, mat4 (core)

//VBE_ASSERT
#ifdef __DEBUG
#ifdef WINDOWS
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
#endif
#else
#define VBE_ASSERT(expression , string)
#endif

//GL_ASSERT
#ifdef __DEBUG
#define GL_ASSERT(gl_code , string) do \
{ \
	gl_code; \
	GLenum __gl_error_code = glGetError(); \
	VBE_ASSERT(__gl_error_code == GL_NO_ERROR, "OpenGL Error with id: " << __gl_error_code << Log::Line << "Reason: " << string); \
} while(0)
#else
#define GL_ASSERT( gl_code , string) gl_code
#endif

//VBE_WARNING
#ifdef __DEBUG
//#define VBE_WARN(msg) Log::warning() << log << Log::Flush
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

//VBE_LOG,_DLOG
#ifdef __LOG
#define VBE_LOG(msg) Log::message() << msg << Log::Flush
#else
#define VBE_LOG(msg)
#endif
#ifdef __DLOG
#define VBE_DLOG(msg) VBE_LOG(msg)
#else
#define VBE_DLOG(msg)
#endif

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
		enum LogModifiers {
			Flush = 0,
			Line,
			Bold
		};

		enum LogFlags {
			Timestamp	= 0x01,
			StandardOut = 0x02,
			AlwaysSave = 0x04,
			GMTime = 0x08
		};

		template<class T> const Log& operator<<(const T& t) const {
			msg << t;
			return *this;
		}

		static void setFlags(unsigned char f) {
			flags = f;
		}

		static Log& message() {
			if(messageInstance == nullptr)
				messageInstance = new Log(Message);
			return *messageInstance;
		}

		static Log& warning() {
			if(warningInstance == nullptr)
				warningInstance = new Log(Warning);
			return *warningInstance;
		}

		static Log& error() {
			if(errorInstance == nullptr)
				errorInstance = new Log(Error);
			return *errorInstance;
		}

		static std::string getContents() { return endFile.str(); }
		static std::string setFilePath() { return endFile.str(); }
};

//Template specialitzations that use private stuff. Implemented in cpp (no actual templating going on)
template<> const Log& Log::operator<< <Log::LogModifiers>(const Log::LogModifiers& t) const;

//Templated, non-member operator overloaders that must be implemented where declared (templates suck at linking)
//User can define them wherever they want for their own objects.
template<class T>
const Log&operator << (const Log& log, const glm::detail::tvec4<T>& v) {
	log << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return log;
}

template<class T>
const Log&operator << (const Log& log, const glm::detail::tvec3<T>& v) {
	log << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return log;
}

template<class T>
const Log&operator << (const Log& log, const glm::detail::tvec2<T>& v) {
	log << "vec2(" << v.x << ", " << v.y << ")";
	return log;
}

template<class T>
const Log&operator << (const Log& log, const glm::detail::tmat3x3<T>& m) {
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
const Log&operator << (const Log& log, const glm::detail::tmat4x4<T>& m) {
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
