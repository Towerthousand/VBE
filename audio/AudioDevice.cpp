#include "AudioDevice.hpp"
#include "ALCheck.hpp"
#include "Listener.hpp"

namespace {
    ALCdevice*  audioDevice  = NULL;
    ALCcontext* audioContext = NULL;
}


AudioDevice::AudioDevice() {
    // Create the device
    audioDevice = alcOpenDevice(NULL);

	if (audioDevice) {
        // Create the context
        audioContext = alcCreateContext(audioDevice, NULL);

		if (audioContext) {
            // Set the context as the current one (we'll only need one)
            alcMakeContextCurrent(audioContext);
        }
		else {
			VBE_ASSERT(!audioContext, "Failed to create the audio context");
        }
    }
	else {
		VBE_ASSERT(!audioDevice, "Failed to open the audio device");
    }
}



AudioDevice::~AudioDevice() {
    // Destroy the context
    alcMakeContextCurrent(NULL);
    if (audioContext)
        alcDestroyContext(audioContext);

    // Destroy the device
    if (audioDevice)
        alcCloseDevice(audioDevice);
}



bool AudioDevice::isExtensionSupported(const std::string& extension) {
    ensureALInit();

    if ((extension.length() > 2) && (extension.substr(0, 3) == "ALC"))
        return alcIsExtensionPresent(audioDevice, extension.c_str()) != AL_FALSE;
    else
        return alIsExtensionPresent(extension.c_str()) != AL_FALSE;
}

int AudioDevice::getFormatFromChannelCount(unsigned int channelCount) {
    ensureALInit();

    // Find the good format according to the number of channels
    int format = 0;
	switch (channelCount) {
        case 1  : format = AL_FORMAT_MONO16;                    break;
        case 2  : format = AL_FORMAT_STEREO16;                  break;
        case 4  : format = alGetEnumValue("AL_FORMAT_QUAD16");  break;
        case 6  : format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
        case 7  : format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
        case 8  : format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
        default : format = 0;                                   break;
    }

    // Fixes a bug on OS X
    if (format == -1)
        format = 0;

    return format;
}
