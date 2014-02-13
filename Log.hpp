#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>

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
#define VBE_WARN(msg) Log::warning() << log << Log::Flush
#define VBE_WARN(expression , string) do \
{ \
	if(!(expression)) { \
		Log::warning() << "Warning Condition Failed " << Log::Line;\
		Log::warning() << "Message: " << string << Log::Line; \
		Log::warning() << "At file " << __FILE__ << \
		 " inside function " << __PRETTY_FUNCTION__ << " on line " << __LINE__ << Log::Flush; \
	} \
} while (0)

//VBE_LOG,_DLOG
#ifdef __LOG
#define VBE_LOG(msg) Log::message() << log << Log::Flush
#else
#define VBE_LOG(msg)
#endif
#ifdef __DLOG
#define VBE_DLOG(msg) VBE_LOG(log)
#else
#define VBE_DLOG(msg)
#endif

class Log {
	private:
		enum logType {
			Message = 0,
			Warning,
			Error
		};

		Log(logType t) : type(t) {}
		~Log() {}

		const logType type;
		mutable std::ostringstream msg;

		static Log* messageInstance;
		static Log* warningInstance;
		static Log* errorInstance;
		static std::ostringstream endFile;
		static unsigned char flags;

	public:
		enum logModifiers {
			Flush = 0,
			Line = 1,
			Bold
		};

		enum logFlags {
			fTimestamp	= 0x01,
			wololo = 0x02
		};

		static void setFlags(unsigned char f) {
			flags = f;
		}

		template<class T>
		const Log& operator<<(const T& t) const {
			msg << t;
			return *this;
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

		static void saveToText(std::string filepath) {
			(void) filepath; //not yet implemented
		}

		static void saveToHtml(std::string filepath) {
			(void) filepath; //not yet implemented
		}

		static std::string getContents() { return endFile.str(); }
};

template<>
const Log& Log::operator<< (const logModifiers& t) const {
	switch(t) {
		case Flush:
			switch(this->type) {
				case Message:
					endFile << "[MESSAGE] "; break;
				case Warning:
					endFile << "[WARNING] "; break;
				case Error:
					endFile << "[ERROR]   "; break; 
				default: break;
			}
			endFile << (flags&fTimestamp?"[":"")
				<< (flags&fTimestamp?"time?":"")
				<< (flags&fTimestamp?"] ":"")
				<< msg.str() << "\n";
			msg.str("");
			break;
		case Line:
			msg << "\n          "; break;
		default: break;
	}
	return *this;
}

#endif // LOG_HPP
