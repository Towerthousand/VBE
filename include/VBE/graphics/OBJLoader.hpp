#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <iostream>

#include <VBE/graphics/MeshSeparate.hpp>
#include <VBE/geometry/AABB.hpp>

class OBJLoader {
    public:
        static MeshSeparate* loadFromOBJStandard(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType, AABB* box = nullptr);
        static MeshSeparate* loadFromOBJTangents(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType, AABB* box = nullptr);

        static void setPositionAttribName(const std::string& name);
        static void setNormalAttribName(const std::string& name);
        static void setTexcoordAttribName(const std::string& name);
        static void setTangentAttribName(const std::string& name);

    private:
        OBJLoader();
        ~OBJLoader();

        static std::string positionAttribName;
        static std::string normalAttribName;
        static std::string texcoordAttribName;
        static std::string tangentAttribName;
};

#endif //OBJLOADER_HPP
