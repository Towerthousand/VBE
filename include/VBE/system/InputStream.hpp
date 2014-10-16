#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

class InputStream {
	public :
		virtual ~InputStream() {}
		virtual long int read(void* data, long int size) = 0;
		virtual long int seek(long int position) = 0;
		virtual long int tell() = 0;
		virtual long int getSize() = 0;
};

#endif // INPUTSTREAM_HPP
