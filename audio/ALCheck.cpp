#include "ALCheck.hpp"
#include "AudioDevice.hpp"

void alCheckError(const std::string& file, unsigned int line) {
	// Get the last error
	ALenum errorCode = alGetError();

	if (errorCode != AL_NO_ERROR) {
		std::string error, description;

		// Decode the error code
		switch (errorCode) {
			case AL_INVALID_NAME :
				error = "AL_INVALID_NAME";
				description = "an unacceptable name has been specified";
				break;
			case AL_INVALID_ENUM :
				error = "AL_INVALID_ENUM";
				description = "an unacceptable value has been specified for an enumerated argument";
				break;
			case AL_INVALID_VALUE :
				error = "AL_INVALID_VALUE";
				description = "a numeric argument is out of range";
				break;
			case AL_INVALID_OPERATION :
				error = "AL_INVALID_OPERATION";
				description = "the specified operation is not allowed in the current state";
				break;
			case AL_OUT_OF_MEMORY :
				error = "AL_OUT_OF_MEMORY";
				description = "there is not enough memory left to execute the command";
				break;
		}

		// Log the error
		VBE_ASSERT(errorCode != AL_NO_ERROR, "An internal OpenAL call failed in "
				   << file.substr(file.find_last_of("\\/") + 1) << " (" << line << ") : "
				   << error << ", " << description);
	}
}

void ensureALInit() {
	static AudioDevice globalDevice;
}
