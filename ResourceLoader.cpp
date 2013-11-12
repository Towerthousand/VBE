#include "ResourceLoader.hpp"

namespace ResourceLoader {
	Mesh* makeMeshFromOBJ(const std::string filepath, Mesh::BufferType bufferType) {
		std::vector<Vertex::Element> elements;
		elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
		elements.push_back(Vertex::Element(Vertex::Attribute::Normal   , Vertex::Element::Float, 3));
		elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

		struct vert {
				vert(vec3f pos, vec3f nor, vec2f tex) : pos(pos) , nor(nor), tex(tex) {}
				vec3f pos,nor;
				vec2f tex;
		};

		std::ifstream in(filepath.c_str(), std::ifstream::in);
		VBE_ASSERT(in, "While importing OBJ: Cannot open " << filepath );

		std::vector<vec3f> vertices;
		std::vector<vec3f> normals;
		std::vector<vec2f> textures;
		std::vector<unsigned int> indices;
		std::vector<vert> data;
		std::vector<vert> data2;

		std::string line;
		while (getline(in, line)) {
			if (line.substr(0,2) == "v ") {
				std::istringstream s(line.substr(2));
				vec3f v;
				s >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			}
			else if (line.substr(0,3) == "vn ") {
				std::istringstream s(line.substr(3));
				vec3f v;
				s >> v.x >> v.y >> v.z;
				normals.push_back(v);
			}
			else if (line.substr(0,3) == "vt ") {
				std::istringstream s(line.substr(3));
				vec2f v;
				s >> v.x >> v.y;
				v.y = 1-v.y;
				textures.push_back(v);
			}
			else if (line.substr(0,2) == "f ") {
				std::istringstream s(line.substr(2));
				std::vector<vec3i> vInf(3,vec3i(0));
				char b;
				s   >> vInf[0].x >> b >> vInf[0].y >> b >> vInf[0].z
					>> vInf[1].x >> b >> vInf[1].y >> b >> vInf[1].z
					>> vInf[2].x >> b >> vInf[2].y >> b >> vInf[2].z;
				vec3i indexes(-1,-1,-1);
				for(unsigned int i = 0; i < 3; ++i)
					for(unsigned int j = 0; j < data.size(); ++j)
						if(data[j].pos == vertices[vInf[i].x-1] &&
						   data[j].tex == textures[vInf[i].y-1] &&
						   data[j].nor == normals[vInf[i].z-1])
							indexes[i] = j;
				for(unsigned int i = 0; i < 3; ++i) {
					if(indexes[i] < 0) {
						indexes[i] = data.size();
						data.push_back(vert(vertices[vInf[i].x-1],normals[vInf[i].z-1],textures[vInf[i].y-1]));
					}
					indices.push_back(indexes[i]);
				}
				data2.push_back(vert(vertices[vInf[0].x-1],normals[vInf[0].z-1],textures[vInf[0].y-1]));
				data2.push_back(vert(vertices[vInf[1].x-1],normals[vInf[1].z-1],textures[vInf[1].y-1]));
				data2.push_back(vert(vertices[vInf[2].x-1],normals[vInf[2].z-1],textures[vInf[2].y-1]));
			}
		}

		float sizeWithoutIndex = data.size();
		float sizeWithIndex = data2.size();

		Mesh* mesh = nullptr;
		if((sizeWithoutIndex/sizeWithIndex) > 1.5) { //indexed
			mesh = new Mesh(bufferType,true);
			mesh->setVertexFormat(Vertex::Format(elements));
			mesh->setVertexData(&data[0],data.size());
			mesh->setVertexIndices(&indices[0],indices.size());
		}
		else { //not indexed
			mesh = new Mesh(bufferType,false);
			mesh->setVertexFormat(Vertex::Format(elements));
			mesh->setVertexData(&data2[0],data2.size());
		}
		return mesh;
	}

	Mesh* makeEmptyMesh(Vertex::Format format, Mesh::BufferType bufferType, bool indexed) {
		Mesh* mesh = new Mesh(bufferType, indexed);
		mesh->setVertexFormat(format);
		return mesh;
	}

} //namespace ResourceLoader
