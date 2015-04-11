#include <string>
#include <vector>
#include <map>

struct AseFloat4
{
	AseFloat4(){}
	AseFloat4(float r_, float g_, float b_, float w_)
	:r(r_), g(g_), b(b_), w(w_){}

	float r = 0, g = 0, b = 0, w = 0;
};

struct AseFloat3
{
	AseFloat3(){}
	AseFloat3(float r_, float g_, float b_)
	:r(r_), g(g_), b(b_){}

	float r = 0, g = 0, b = 0;
};

struct AseMaterial
{
	AseFloat4 ambient;
	AseFloat4 diffuse;
	AseFloat4 specular;

	std::string texture = "";
	float uTile = 0, vTile = 0;
};

struct AseVertex
{
	AseFloat3 pos;
	AseFloat3 normal;
	AseFloat3 texPos;
};

struct AseMesh
{
	AseMesh()
	: translation(0,0,0),scale(1,1,1),rotateAxis(0,0,0),rotateAngle(0)
	{}

	std::vector<AseVertex> vertices;
	std::vector<unsigned> indices;

	AseMesh* parent = nullptr;
	AseFloat3 translation;
	AseFloat3 scale;
	AseFloat3 rotateAxis;
	float rotateAngle;
};

class Converter
{
public:
	Converter();
	~Converter();

	bool parse(const std::string& fileName);
	void printInfo();
	bool out(const std::string& fileName, const std::string& meshName, const std::string& materialName);

private:
	void tokenize(const std::string& line);
	void parseScene();
	void parseMaterialList();

	void parseMaterial();

	void parseTexture(AseMaterial& mat);

	void parseMesh();
	void parseMeshInfo(AseMesh& mesh);
	void parseVertex(AseMesh& mesh);
	void parseFace(AseMesh& mesh);
	void parseTVertex(std::vector<AseFloat3>& tVertices);
	void parseTFace(AseMesh& mesh, const std::vector<AseFloat3>& tVertices);
	void parseNormal(AseMesh& mesh);
	void parseAnimation(AseMesh& mesh);


	using Tokens = std::vector<std::string>;

	Tokens tokens;
	int idx = 0;

	AseFloat3 sceneAmbient;

	std::map<std::string, AseMesh> meshes;
	std::map<std::string, AseMaterial> materials;
};