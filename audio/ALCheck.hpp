#ifndef ALCHECK_HPP
#define ALCHECK_HPP
#include "tools.hpp"
#include "utils/InputStream.hpp"

// Let's define a macro to quickly check every OpenAL API calls
#ifdef __DEBUG
    // If in debug mode, perform a test on every call
	#define alCheck(x) x; alCheckError(__FILE__, __LINE__);
#else
    // Else, we don't add any overhead
    #define alCheck(Func) (Func)
#endif //__DEBUG
void alCheckError(const std::string& file, unsigned int line);
void ensureALInit();
#endif // ALCHECK_HPP
