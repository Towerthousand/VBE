#ifndef STORAGEIMPL_H
#define STORAGEIMPL_H

#include <iostream>
#include <memory>
#include <string>

class StorageImpl {
	public:
		static std::unique_ptr<std::istream> openAsset(const std::string& filename);
};


#endif // STORAGEIMPL_H
