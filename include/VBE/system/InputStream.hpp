#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP


///
/// \brief The InputStream class can be used to read an input stream of data.
/// Several implementations exist that read from several sources, such as
/// FileInputStream, which reads from regular files, or ResourceInputStream, which
/// reads from asset files in the APK in Android.
///
class InputStream {
	public :
		virtual ~InputStream() = default;
		virtual long int read(void* data, long int size) = 0;
		virtual long int seek(long int position) = 0;
		virtual long int tell() = 0;
		virtual long int getSize() = 0;
};

#endif // INPUTSTREAM_HPP
