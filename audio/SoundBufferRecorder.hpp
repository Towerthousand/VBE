#ifndef SOUNDBUFFERRECORDER_HPP
#define SOUNDBUFFERRECORDER_HPP
#include "SoundBuffer.hpp"
#include "SoundRecorder.hpp"

class SoundBufferRecorder : public SoundRecorder {
	public :
		const SoundBuffer& getBuffer() const;

	protected:
		virtual bool onStart();
		virtual bool onProcessSamples(const short* samples, std::size_t sampleCount);
		virtual void onStop();

	private :
		std::vector<short> m_samples; ///< Temporary sample buffer to hold the recorded data
		SoundBuffer        m_buffer;  ///< Sound buffer that will contain the recorded data
};

#endif // SOUNDBUFFERRECORDER_HPP
