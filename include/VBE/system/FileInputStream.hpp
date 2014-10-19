#ifndef FILEINPUTSTREAM_HPP
#define FILEINPUTSTREAM_HPP

#include <string>
#include <fstream>

#include <VBE/system/InputStream.hpp>

class FileInputStream : public InputStream {
	public:
		FileInputStream(std::string filename);
		~FileInputStream() override;

		long int read(void* data, long int size) override;
		long int seek(long int position) override;
		long int tell() override;
		long int getSize() override;

	private:
		std::ifstream in;
		long int size;
};

#endif // FILEINPUTSTREAM_HPP
