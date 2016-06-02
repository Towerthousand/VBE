#include <VBE/graphics/Mesh.hpp>
#include <VBE/graphics/MeshIndexed.hpp>
#include <VBE/graphics/OBJLoader.hpp>
#include <VBE/math.hpp>
#include <VBE/system/Log.hpp>

std::string OBJLoader::positionAttribName = "position";
std::string OBJLoader::normalAttribName = "normal";
std::string OBJLoader::texcoordAttribName = "texcoord";
std::string OBJLoader::tangentAttribName = "tangents";

struct FunctorComparevec3i{
        bool operator()(const vec3i& a, const vec3i& b) const {
            if(a.x != b.x) return a.x < b.x;
            if(a.y != b.y) return a.y < b.y;
            if(a.z != b.z) return a.z < b.z;
            return false;
        }
};


void OBJLoader::setPositionAttribName(const std::string& name) {
    positionAttribName = name;
}

void OBJLoader::setNormalAttribName(const std::string& name) {
    normalAttribName = name;
}

void OBJLoader::setTexcoordAttribName(const std::string& name) {
    texcoordAttribName = name;
}

void OBJLoader::setTangentAttribName(const std::string& name) {
    tangentAttribName = name;
}

MeshSeparate* OBJLoader::loadFromOBJStandard(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType, AABB* box) {
    VBE_DLOG("* Loading new OBJ from file. Expected format: V/T/N");
    std::vector<Vertex::Attribute> elements;
    elements.push_back(Vertex::Attribute(positionAttribName, Vertex::Attribute::Float, 3));
    elements.push_back(Vertex::Attribute(normalAttribName, Vertex::Attribute::Float, 3));
    elements.push_back(Vertex::Attribute(texcoordAttribName, Vertex::Attribute::Float, 2));

    struct vert {
            vert(vec3f pos, vec3f nor, vec2f tex) : pos(pos) , nor(nor), tex(tex) {}
            vec3f pos, nor;
            vec2f tex;
    };

    std::vector<vec3f> vertices;
    std::vector<vec3f> normals;
    std::vector<vec2f> textures;
    std::vector<unsigned int> indices;
    std::vector<vert> dataIndexed;
    std::vector<vert> dataNotIndexed;
    std::map<vec3i, int, FunctorComparevec3i> indexMap;

    AABB loadedBox;

    std::string line;
    while (getline(*in, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            vec3f v;
            s >> v.x >> v.y >> v.z;
            vertices.push_back(v);

            loadedBox.extend(v);
        }
        else if (line.substr(0, 3) == "vn ") {
            std::istringstream s(line.substr(3));
            vec3f v;
            s >> v.x >> v.y >> v.z;
            normals.push_back(v);
        }
        else if (line.substr(0, 3) == "vt ") {
            std::istringstream s(line.substr(3));
            vec2f v;
            s >> v.x >> v.y;
            v.y = 1-v.y;
            textures.push_back(v);
        }
        //f 1/1/1 2/2/2 3/3/3
        else if (line.substr(0, 2) == "f ") {
            std::istringstream s(line.substr(2));
            std::vector<vec3i> vInf(3, vec3i(0));
            char b;
            s   >> vInf[0].x >> b >> vInf[0].y >> b >> vInf[0].z
                    >> vInf[1].x >> b >> vInf[1].y >> b >> vInf[1].z
                    >> vInf[2].x >> b >> vInf[2].y >> b >> vInf[2].z;
            for(unsigned int i = 0; i < 3; ++i) {
                std::map<vec3i, int, FunctorComparevec3i>::iterator it = indexMap.find(vInf[i]);
                int ind = 0;
                if(it == indexMap.end()) {
                    ind = indexMap.size();
                    indexMap.insert(std::pair<vec3i, int>(vInf[i], dataIndexed.size()));
                    dataIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], textures[vInf[i].y-1]));
                }
                else ind = it->second;
                indices.push_back(ind);
                dataNotIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], textures[vInf[i].y-1]));
            }
        }
    }
    int sizeWithIndex = dataIndexed.size()*sizeof(vert)+indices.size()*sizeof(int);
    int sizeWithoutIndex = dataNotIndexed.size()*sizeof(vert);

    VBE_DLOG(" - Vertex count without indexes: " << dataNotIndexed.size());
    VBE_DLOG(" - Vertex count with indexes: " << dataIndexed.size() << " (" << indices.size() << ") indexes");
    VBE_DLOG(" - Size with indexes: " << sizeWithIndex << ". Size without indexes: " << sizeWithoutIndex);
    MeshSeparate* mesh = nullptr;
    if(sizeWithoutIndex > sizeWithIndex) { //indexed
        mesh = new MeshIndexed(Vertex::Format(elements), bufferType);
        mesh->setVertexData(&dataIndexed[0], dataIndexed.size());
        ((MeshIndexed*)mesh)->setIndexData(&indices[0], indices.size());
        VBE_DLOG("    Using indexes");
    }
    else { //not indexed
        mesh = new Mesh(Vertex::Format(elements), bufferType);
        mesh->setVertexData(&dataNotIndexed[0], dataNotIndexed.size());
        VBE_DLOG("    Not using indexes");
    }

    if (box != nullptr) {
        *box = loadedBox;
    }
    return mesh;
}

MeshSeparate* OBJLoader::loadFromOBJTangents(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType, AABB* box) {
    VBE_DLOG("* Loading new OBJ from file. Expected format: V/T/N");
    std::vector<Vertex::Attribute> elements;
    elements.push_back(Vertex::Attribute(positionAttribName, Vertex::Attribute::Float, 3));
    elements.push_back(Vertex::Attribute(normalAttribName, Vertex::Attribute::Float, 3));
    elements.push_back(Vertex::Attribute(tangentAttribName, Vertex::Attribute::Float, 3));
    elements.push_back(Vertex::Attribute(texcoordAttribName, Vertex::Attribute::Float, 2));

    struct vert {
            vert(vec3f pos, vec3f nor, vec3f tan, vec2f tex) : pos(pos) , nor(nor), tan(tan), tex(tex) {}
            vec3f pos, nor, tan;
            vec2f tex;
    };

    std::vector<vec3f> vertices;
    std::vector<vec3f> normals;
    std::vector<vec3f> tangents;
    std::vector<vec2f> textures;
    std::vector<unsigned int> indices;
    std::vector<vert> dataIndexed;
    std::vector<vert> dataNotIndexed;
    std::map<vec3i, int, FunctorComparevec3i> indexMap;

    AABB loadedBox;

    std::string line;
    while (getline(*in, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            vec3f v;
            s >> v.x >> v.y >> v.z;
            vertices.push_back(v);

            loadedBox.extend(v);
        }
        else if (line.substr(0, 3) == "vn ") {
            std::istringstream s(line.substr(3));
            vec3f v;
            s >> v.x >> v.y >> v.z;
            normals.push_back(v);
            vec3f t = glm::cross(glm::normalize(v), vec3f(0, 0, 1));
            if (glm::length(t) < 0.01) t = glm::cross(glm::normalize(v), vec3f(0, 1, 0));
            tangents.push_back(t);
        }
        else if (line.substr(0, 3) == "vt ") {
            std::istringstream s(line.substr(3));
            vec2f v;
            s >> v.x >> v.y;
            v.y = 1-v.y;
            textures.push_back(v);
        }
        else if (line.substr(0, 2) == "f ") {
            std::istringstream s(line.substr(2));
            std::vector<vec3i> vInf(3, vec3i(0));
            char b;
            s   >> vInf[0].x >> b >> vInf[0].y >> b >> vInf[0].z
                    >> vInf[1].x >> b >> vInf[1].y >> b >> vInf[1].z
                    >> vInf[2].x >> b >> vInf[2].y >> b >> vInf[2].z;
            for(unsigned int i = 0; i < 3; ++i) {
                std::map<vec3i, int, FunctorComparevec3i>::iterator it = indexMap.find(vInf[i]);
                int ind = 0;
                if(it == indexMap.end()) {
                    ind = indexMap.size();
                    indexMap.insert(std::pair<vec3i, int>(vInf[i], dataIndexed.size()));
                    dataIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], tangents[vInf[i].z-1], textures[vInf[i].y-1]));
                }
                else ind = it->second;
                indices.push_back(ind);
                dataNotIndexed.push_back(vert(vertices[vInf[i].x-1], normals[vInf[i].z-1], tangents[vInf[i].z-1], textures[vInf[i].y-1]));
            }
        }
    }
    int sizeWithIndex = dataIndexed.size()*sizeof(vert)+indices.size()*sizeof(int);
    int sizeWithoutIndex = dataNotIndexed.size()*sizeof(vert);

    VBE_DLOG(" - Vertex count without indexes: " << dataNotIndexed.size());
    VBE_DLOG(" - Vertex count with indexes: " << dataIndexed.size() << " (" << indices.size() << ") indexes");
    VBE_DLOG(" - Size with indexes: " << sizeWithIndex << ". Size without indexes: " << sizeWithoutIndex);
    MeshSeparate* mesh = nullptr;
    if(sizeWithoutIndex > sizeWithIndex) { //indexed
        mesh = new MeshIndexed(Vertex::Format(elements), bufferType);
        mesh->setVertexData(&dataIndexed[0], dataIndexed.size());
        ((MeshIndexed*)mesh)->setIndexData(&indices[0], indices.size());
        VBE_DLOG("    Using indexes");
    }
    else { //not indexed
        mesh = new Mesh(Vertex::Format(elements), bufferType);
        mesh->setVertexData(&dataNotIndexed[0], dataNotIndexed.size());
        VBE_DLOG("    Not using indexes");
    }

    if (box != nullptr) {
        *box = loadedBox;
    }
    return mesh;
}
