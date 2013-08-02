#ifndef MODEL_H
#define MODEL_H
#include "tools.hpp"

struct ModelCubeFileFormat;
struct ModelCube { //has no texture
		ModelCube (bool isAir, vec3f color);
		ModelCube (const ModelCubeFileFormat& c);
		bool isAir;
		vec3f color;
};

struct ModelCubeFileFormat { //has no texture
		ModelCubeFileFormat(const ModelCube &c);
		unsigned char r, g, b;
		bool isAir;
};

struct ModelVertex {
		ModelVertex(float vx = 0.0, float vy = 0.0, float vz = 0.0,
			   float cr = 1.0, float cg = 1.0, float cb = 1.0, float ca = 1.0) :
			vx(vx), vy(vy), vz(vz),
			cr(cr), cg(cg), cb(cb), ca(ca)
		{}
		float
		vx,vy,vz,
		cr,cg,cb,ca;
};

class Model {
	public:
		Model();
		~Model();

		bool loadVoxelization(const std::string &filePath);
		void draw() const;

		int modelWidth; //in model cubes
		int modelHeight;//in model cubes
		int modelDepth; //in model cubes
	private:
		ModelCube getCube(int x, int y, int z);
		void pushCubeToArray(int x, int y, int z, std::vector<ModelVertex> &renderData);
		void makeVbo(std::vector<ModelVertex> &renderData);

		int VBOID;
		int vertexCount;
		std::vector<std::vector<std::vector<ModelCube> > > cubes;
};

#endif // MODEL_H
