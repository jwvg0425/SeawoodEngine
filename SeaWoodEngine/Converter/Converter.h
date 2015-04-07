#include <string>
#include <vector>
#include <map>

struct AseFloat4
{
	float r = 0, g = 0, b = 0, w = 0;
};

struct AseFloat3
{
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
	std::vector<AseVertex> vertices;
	std::vector<unsigned> indices;
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


	using Tokens = std::vector<std::string>;

	Tokens tokens;
	int idx = 0;

	AseFloat3 sceneAmbient;

	std::map<std::string, AseMesh> meshes;
	std::map<std::string, AseMaterial> materials;
};