#include "Log.hpp"

std::ostringstream Log::endFile;
unsigned char Log::flags = 0x00;
Log* Log::messageInstance = nullptr;
Log* Log::warningInstance = nullptr;
Log* Log::errorInstance   = nullptr;
