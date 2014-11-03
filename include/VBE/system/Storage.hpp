#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <iostream>
#include <memory>
#include <string>

class Storage {
	public:
		static std::unique_ptr<std::istream> openAsset(const std::string& filename);
		static std::string readToString(std::unique_ptr<std::istream> file);
};

#endif // STORAGE_HPP
