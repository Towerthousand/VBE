#ifndef SOUNDBUFFER_HPP
#define SOUNDBUFFER_HPP
#include "SoundFile.hpp"

class Sound;
class InputStream;

class SoundBuffer {
	public :
		SoundBuffer();
		SoundBuffer(const SoundBuffer& copy);
		~SoundBuffer();

		bool loadFromFile(const std::string& filename);
		bool loadFromMemory(const void* data, std::size_t sizeInBytes);
		bool loadFromStream(InputStream& stream);
		bool loadFromSamples(const short* samples, std::size_t sampleCount, unsigned int channelCount, unsigned int sampleRate);
		bool saveToFile(const std::string& filename) const;
		const short* getSamples() const;
		std::size_t getSampleCount() const;
		unsigned int getSampleRate() const;
		unsigned int getChannelCount() const;
		float getDuration() const;
		SoundBuffer& operator =(const SoundBuffer& right);

	private :
		friend class Sound;
		bool initialize(SoundFile& file);
		bool update(unsigned int channelCount, unsigned int sampleRate);
		void attachSound(Sound* sound) const;
		void detachSound(Sound* sound) const;

		typedef std::set<Sound*> SoundList; ///< Set of unique sound instances

		unsigned int       m_buffer;   ///< OpenAL buffer identifier
		std::vector<short> m_samples;  ///< Samples buffer
		float               m_duration; ///< Sound duration
		mutable SoundList  m_sounds;   ///< List of sounds that are using this buffer
};

#endif // SOUNDBUFFER_HPP
