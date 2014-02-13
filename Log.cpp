#include "Log.hpp"
#include <iomanip>
#include <ctime>

std::ostringstream Log::endFile;
unsigned char Log::flags = Log::fTimestamp|Log::fAlwaysSave|Log::fStandardOut;
Log* Log::messageInstance = nullptr;
Log* Log::warningInstance = nullptr;
Log* Log::errorInstance   = nullptr;
std::string Log::outPath = "log.txt";

template<>
const Log& Log::operator<< (const logModifiers& t) const {
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
				if(flags&fTimestamp) {
					std::time_t time = std::time(nullptr);
					std::tm* t = (flags&fGMTime?std::gmtime(&time):std::localtime(&time));
					msg << "[" << (t->tm_hour<10?"0":"") << t->tm_hour << ":" << (t->tm_min<10?"0":"") << t->tm_min << ":" << (t->tm_sec<10?"0":"") << t->tm_sec << "] ";
				}
				msg << content << "\n";
				if(flags&fStandardOut) {
					std::cout << msg.str();
					std::cout.flush();
				}
				endFile << msg.str();
				msg.str("");
				if(flags&fAlwaysSave) save();
				break;
			}
		case Line:
			msg << "\n          " << (flags&fTimestamp?"           ":""); break;
		default: break;
	}
	return *this;
}
