#ifndef MUSIC_HPP
#define MUSIC_HPP
#include "SoundStream.hpp"
#include "SoundFile.hpp"

class InputStream;
class Music : public SoundStream {
	public :
		Music();
		~Music();
		bool openFromFile(const std::string& filename);
		bool openFromMemory(const void* data, std::size_t sizeInBytes);
		bool openFromStream(InputStream& stream);
		float getDuration() const;

	protected :
		virtual bool onGetData(Chunk& data);
		virtual void onSeek(float timeOffset);

	private :
		void initialize();

		SoundFile*   m_file;     // Sound file
		float               m_duration; // Music duration
		std::vector<short> m_samples;  // Temporary buffer of samples
		std::mutex              m_Mutex;    // std::mutex protecting the data
};

#endif // MUSIC_HPP
