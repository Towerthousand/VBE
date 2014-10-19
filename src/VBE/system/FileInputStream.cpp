#include <VBE/system/FileInputStream.hpp>

using namespace std;

FileInputStream::FileInputStream(string filename) {
	in.open(filename);
	in.seekg(0, ios_base::end);
	size = in.tellg();
	in.seekg(0, ios_base::beg);
}

FileInputStream::~FileInputStream() {
	in.close();
}

long int FileInputStream::read(void* data, long int size) {
	in.read((char*)data, size);
}

long int FileInputStream::seek(long int position) {
	in.seekg(position, ios_base::beg);
}

long int FileInputStream::tell() {
	return in.tellg();
}

long int FileInputStream::getSize() {
	return size;
}
