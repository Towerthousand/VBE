#include "Log.hpp"
#include <ctime>

std::ostringstream Log::endFile;
#ifndef VBE_GLES2
unsigned char Log::flags = Log::Timestamp|Log::AlwaysSave|Log::StandardOut;
#else
unsigned char Log::flags = Log::Timestamp|Log::StandardOut;
#endif
Log* Log::messageInstance = nullptr;
Log* Log::warningInstance = nullptr;
Log* Log::errorInstance   = nullptr;
std::string Log::outPath = "log.txt";

template<> const Log& Log::operator<< (const Log::LogModifiers& t) const {
	switch(t) {
		case Flush:
		{
			std::string content = msg.str();
			msg.str("");
			switch(this->type) {
				case Message:
					msg << "[MESSAGE] "; break;
				case Warning:
					msg << "[WARNING] "; break;
				case Error:
					msg << "[ERROR]   "; break;
				default: break;
			}
			if(flags&Timestamp) {
				std::time_t time = std::time(nullptr);
				std::tm* t = (flags&GMTime?std::gmtime(&time):std::localtime(&time));
				msg << "[" << (t->tm_hour<10?"0":"") << t->tm_hour << ":" << (t->tm_min<10?"0":"") << t->tm_min << ":" << (t->tm_sec<10?"0":"") << t->tm_sec << "] ";
			}
			msg << content << "\n";
			if(flags&StandardOut) {
#ifndef VBE_GLES2
				std::cout << msg.str();
				std::cout.flush();
#else
				__android_log_print(ANDROID_LOG_INFO, "VBE", msg.c_str());
#endif
			}
			endFile << msg.str();
			msg.str("");
#ifndef VBE_GLES2
			if(flags&AlwaysSave) save();
#endif
			break;
		}
		case Line:
			msg << "\n          " << (flags&Timestamp?"           ":""); break;
		default: break;
	}
	return *this;
}
