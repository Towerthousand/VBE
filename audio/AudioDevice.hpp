#ifndef AUDIODEVICE_HPP
#define AUDIODEVICE_HPP
#include "tools.hpp"

class AudioDevice {
	public :
		AudioDevice();
		~AudioDevice();

		static bool isExtensionSupported(const std::string& extension);
		static int getFormatFromChannelCount(unsigned int channelCount);
};

#endif // AUDIODEVICE_HPP
