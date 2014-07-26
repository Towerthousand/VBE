#ifndef SOUNDSTREAM_HPP
#define SOUNDSTREAM_HPP
#include "SoundSource.hpp"

class SoundStream : public SoundSource {
	public :
		struct Chunk {
				const short* samples;     // Pointer to the audio samples
				std::size_t  sampleCount; // Number of samples pointed by Samples
		};

		virtual ~SoundStream();

		void play();
		void pause();
		void stop();
		unsigned int getChannelCount() const;
		unsigned int getSampleRate() const;
		Status getStatus() const;
		void setPlayingOffset(float timeOffset);
		float getPlayingOffset() const;
		void setLoop(bool loop);
		bool getLoop() const;

	protected :
		SoundStream();

		void initialize(unsigned int channelCount, unsigned int sampleRate);
		virtual bool onGetData(Chunk& data) = 0;
		virtual void onSeek(float timeOffset) = 0;

	private :
		void streamData();
		bool fillAndPushBuffer(unsigned int bufferNum);
		bool fillQueue();
		void clearQueue();

		enum {
			BufferCount = 3 ///< Number of audio buffers used by the streaming loop
		};

		std::thread        m_thread;				// Thread running the background tasks
		mutable std::mutex m_threadMutex;			// Thread std::mutex
		Status        m_threadStartState;			// State the thread starts in (Playing, Paused, Stopped)
		bool          m_isStreaming;				// Streaming state (true = playing, false = stopped)
		unsigned int  m_buffers[BufferCount];		// Sound buffers used to store temporary audio data
		unsigned int  m_channelCount;				// Number of channels (1 = mono, 2 = stereo, ...)
		unsigned int  m_sampleRate;					// Frequency (samples / second)
		Uint32        m_format;						// Format of the internal sound buffers
		bool          m_loop;						// Loop flag (true to loop, false to play once)
		unsigned long int m_samplesProcessed;       // Number of buffers processed since beginning of the stream
		bool          m_endBuffers[BufferCount];    // Each buffer is marked as "end buffer" or not, for proper duration calculation
};

#endif // SOUNDSTREAM_HPP
