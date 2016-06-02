#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <iostream>
#include <memory>
#include <string>

///
/// \brief The Storage class lets you open assets
///
class Storage {
    public:
        ///
        /// \brief openAsset Opens the specified asset. Assets are looked up relative to the asset path.
        /// \param filename The file to open
        /// \return The stream that represents the file
        ///
        static std::unique_ptr<std::istream> openAsset(const std::string& filename);

        ///
        /// \brief readToString Read an std::istream into a string.
        /// \param file The file to read
        /// \return The string with the file's contents
        ///
        static std::string readToString(std::unique_ptr<std::istream> file);

        ///
        /// \brief Sets the asset path.
        /// \param path The new asset path.
        ///
        static void setAssetPath(std::string path);
};
///
/// \class Storage Storage.hpp <VBE/system/Storage.hpp>
///	\ingroup System
///
/// With this class you can open arbitrary filepaths as streams, and read them into strings.
///

#endif // STORAGE_HPP
