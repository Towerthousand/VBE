#ifndef SOUNDRECORDER_HPP
#define SOUNDRECORDER_HPP
#include "tools.hpp"

class SoundRecorder {
	public :
		virtual ~SoundRecorder();

		bool start(unsigned int sampleRate = 44100);
		void stop();
		unsigned int getSampleRate() const;
		static std::vector<std::string> getAvailableDevices();
		static std::string getDefaultDevice();
		bool setDevice(const std::string& name);
		const std::string& getDevice() const;
		static bool isAvailable();

	protected :
		SoundRecorder();
		void setProcessingInterval(float interval);
		virtual bool onStart();
		virtual bool onProcessSamples(const short* samples, std::size_t sampleCount) = 0;
		virtual void onStop();

	private :
		void record();
		void processCapturedSamples();
		void cleanup();

		std::thread             m_thread;        // Thread running the background recording task
		std::vector<short> m_samples;            // Buffer to store captured samples
		unsigned int       m_sampleRate;         // Sample rate
		float           m_processingInterval;    // float period between calls to onProcessSamples
		bool               m_isCapturing;        // Capturing state
		std::string        m_deviceName;         // Name of the audio capture device
};

#endif // SOUNDRECORDER_HPP
