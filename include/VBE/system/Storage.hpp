#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <iostream>

class Storage {
	public:
		static std::istream* openAsset(const std::string& filename);
};

#endif // STORAGE_HPP
