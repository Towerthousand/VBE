#ifndef STORAGEIMPL_H
#define STORAGEIMPL_H

#include <string>
#include <iostream>

class StorageImpl {
	public:
		static std::istream* openAsset(const std::string& filename);
};


#endif // STORAGEIMPL_H
