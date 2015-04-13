#include <string>
#include <vector>
#include <map>
#include <fstream>

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
	std::string parentName;
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

	AseFloat3 translation;
	AseFloat3 scale;
	AseFloat3 rotateAxis;
	float rotateAngle;
};

struct AseNode
{
	AseNode() : name(""), parentName("") {}

	std::string name;
	std::string parentName;
	std::vector<AseMesh> meshes;
	int materialIndex = 0;
};

class Converter
{
public:
	Converter();
	~Converter();

	bool parse(const std::string& fileName);
	void printInfo();
	bool out(const std::string& fileName, const std::string& nodeName);

private:
	void outMaterial(std::ofstream& file, const std::string& MaterialName);
	void outNode(std::ofstream& file, const std::string& nodeName);

	void tokenize(const std::string& line);
	void parseScene();
	void parseMaterialList();

	void parseMaterial(const std::string& parent);

	void parseTexture(AseMaterial& mat);

	void parseNode();
	void parseMesh(AseNode& node);
	void parseVertex(AseMesh& mesh);
	void parseFace(AseMesh& mesh);
	void parseTVertex(std::vector<AseFloat3>& tVertices);
	void parseTFace(AseMesh& mesh, const std::vector<AseFloat3>& tVertices);
	void parseNormal(AseMesh& mesh);
	void parseAnimation(AseNode& mesh);


	using Tokens = std::vector<std::string>;

	Tokens tokens;
	int idx = 0;

	AseFloat3 sceneAmbient;

	std::map<std::string, AseNode> nodes;
	std::map<std::string, AseMaterial> materials;
};