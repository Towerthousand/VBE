#ifndef STORAGEIMPL_H
#define STORAGEIMPL_H

#include <memory>
#include <string>
#include <iostream>

class StorageImpl {
    public:
        static std::unique_ptr<std::istream> openAsset(const std::string& filename);
};


#endif // STORAGEIMPL_H
