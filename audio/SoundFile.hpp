#ifndef SOUNDFILE_HPP
#define SOUNDFILE_HPP
#include <sndfile.h>
#include <string>
#include "utils/InputStream.hpp"
#include "tools.hpp"

class SoundFile {
	public :
		SoundFile();
		~SoundFile();

		std::size_t getSampleCount() const;
		unsigned int getChannelCount() const;
		unsigned int getSampleRate() const;
		bool openRead(const std::string& filename);
		bool openRead(const void* data, std::size_t sizeInBytes);
		bool openRead(InputStream& stream);
		bool openWrite(const std::string& filename, unsigned int channelCount, unsigned int sampleRate);
		std::size_t read(short* data, std::size_t sampleCount);
		void write(const short* data, std::size_t sampleCount);
		void seek(float timeOffset);

	private :
		void initialize(SF_INFO fileInfo);
		static int getFormatFromFilename(const std::string& filename);

		struct Memory
		{
				const char* begin;
				const char* current;
				sf_count_t  size;

				static sf_count_t getLength(void* user);
				static sf_count_t read(void* ptr, sf_count_t count, void* user);
				static sf_count_t seek(sf_count_t offset, int whence, void* user);
				static sf_count_t tell(void* user);
		};

		struct Stream
		{
				InputStream* source;
				long int size;

				static sf_count_t getLength(void* user);
				static sf_count_t read(void* ptr, sf_count_t count, void* user);
				static sf_count_t seek(sf_count_t offset, int whence, void* user);
				static sf_count_t tell(void* user);
		};

		SNDFILE*     m_file;         ///< File descriptor
		Memory       m_memory;       ///< Memory reading info
		Stream       m_stream;       ///< Stream reading info
		std::size_t  m_sampleCount;  ///< Total number of samples in the file
		unsigned int m_channelCount; ///< Number of channels used by the sound
		unsigned int m_sampleRate;   ///< Number of samples per second
};

#endif // SOUNDFILE_HPP
