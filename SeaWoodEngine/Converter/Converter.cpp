#include "Converter.h"
#include <fstream>
#include <iostream>

Converter::Converter()
{

}

Converter::~Converter()
{

}

bool Converter::parse(const std::string& fileName)
{
	std::ifstream file;

	file.open(fileName);

	if (!file.is_open())
	{
		return false;
	}

	const size_t BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];

	//tokenize
	while (!file.eof()){
		file.getline(buffer, BUFFER_SIZE);
		tokenize(buffer);
	}
	file.close();

	//parse
	while (idx < tokens.size())
	{
		if (tokens[idx] == "*SCENE")
		{
			idx += 2;
			parseScene();
		}
		else if (tokens[idx] == "*MATERIAL_LIST")
		{
			idx += 2;
			parseMaterialList();
		}
		else if (tokens[idx] == "*GEOMOBJECT")
		{
			idx += 2;
			parseMesh();
		}

		idx++;
	}

	return true;
}

void Converter::printInfo()
{
	std::cout << std::endl << " *** Material *** " << std::endl << std::endl;

	for (auto& material : materials)
	{
		std::cout << material.first << std::endl;
	}

	std::cout << std::endl << " *** Mesh *** " << std::endl << std::endl;

	for (auto& mesh : meshes)
	{
		std::cout << mesh.first << std::endl;
	}

	std::cout << std::endl;
}

bool Converter::out(const std::string& fileName, const std::string& meshName, const std::string& materialName)
{
	std::ofstream file;

	file.open(fileName + ".swm", std::ios_base::out | std::ios_base::binary);

	if (!file.is_open())
	{
		return false;
	}

	AseMesh mesh = meshes[meshName];
	AseMaterial material = materials[materialName];
	int size = mesh.vertices.size();

	file.write((const char*)&size, sizeof(size_t));

	for (auto& vertex : mesh.vertices)
	{
		file.write((const char*)&vertex.pos.r, sizeof(float));
		file.write((const char*)&vertex.pos.g, sizeof(float));
		file.write((const char*)&vertex.pos.b, sizeof(float));

		file.write((const char*)&vertex.normal.r, sizeof(float));
		file.write((const char*)&vertex.normal.g, sizeof(float));
		file.write((const char*)&vertex.normal.b, sizeof(float));

		file.write((const char*)&vertex.texPos.r, sizeof(float));
		file.write((const char*)&vertex.texPos.g, sizeof(float));
	}

	size = mesh.indices.size();

	file.write((const char*)&size, sizeof(size_t));

	for (auto index : mesh.indices)
	{
		file.write((const char*)&index, sizeof(unsigned));
	}

	file.write((const char*)&material.ambient.r, sizeof(float));
	file.write((const char*)&material.ambient.g, sizeof(float));
	file.write((const char*)&material.ambient.b, sizeof(float));
	file.write((const char*)&material.ambient.w, sizeof(float));

	file.write((const char*)&material.diffuse.r, sizeof(float));
	file.write((const char*)&material.diffuse.g, sizeof(float));
	file.write((const char*)&material.diffuse.b, sizeof(float));
	file.write((const char*)&material.diffuse.w, sizeof(float));

	file.write((const char*)&material.specular.r, sizeof(float));
	file.write((const char*)&material.specular.g, sizeof(float));
	file.write((const char*)&material.specular.b, sizeof(float));
	file.write((const char*)&material.specular.w, sizeof(float));

	file.write((const char*)&material.uTile, sizeof(float));
	file.write((const char*)&material.vTile, sizeof(float));

	size = material.texture.size();

	file.write((const char*)&size, sizeof(size_t));

	file.write(material.texture.c_str(), sizeof(char)*size);


	return true;
}

void Converter::tokenize(const std::string& line)
{
	std::string token;
	bool isInString = false;

	for (auto& ch : line)
	{
		//문자열 안에 있는건 싹 다 넣어야한다
		if (isInString)
		{
			//문자열 종료
			if (ch == '\"')
			{
				tokens.push_back(token);
				isInString = false;
				token = "";
			}
			else
			{
				token += ch;
			}

		}
		else if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ':') //토큰 구분 단위
		{
			if (token != "")
			{
				tokens.push_back(token);
				token = "";
			}
		}
		else if (ch == '\"')//문자열 시작
		{
			if (token != "")
			{
				tokens.push_back(token);
				token = "";
			}
			isInString = true;
		}
		else //그 외의 글자들은 토큰에 포함.
		{
			token += ch;
		}
	}

	if (token != "")
	{
		tokens.push_back(token);
	}
}

void Converter::parseScene()
{
	while (tokens[idx] != "}")
	{
		//scene ambient값 구하기
		if (tokens[idx] == "*SCENE_AMBIENT_STATIC")
		{
			sceneAmbient.r = atof(tokens[idx + 1].c_str());
			sceneAmbient.g = atof(tokens[idx + 2].c_str());
			sceneAmbient.b = atof(tokens[idx + 3].c_str());
			idx += 3;
		}
		idx++;
	}
}

void Converter::parseMaterialList()
{
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MATERIAL")
		{
			idx += 3;
			parseMaterial();
		}
		idx++;
	}
}

void Converter::parseMaterial()
{
	std::string name;
	AseMaterial material;

	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MATERIAL_NAME")
		{
			name = tokens[idx + 1];
			idx += 1;
		}
		else if (tokens[idx] == "*MATERIAL_AMBIENT")
		{
			material.ambient.r = atof(tokens[idx + 1].c_str());
			material.ambient.g = atof(tokens[idx + 2].c_str());
			material.ambient.b = atof(tokens[idx + 3].c_str());
			material.ambient.w = 1.0f;
			idx += 3;
		}
		else if (tokens[idx] == "*MATERIAL_DIFFUSE")
		{
			material.diffuse.r = atof(tokens[idx + 1].c_str());
			material.diffuse.g = atof(tokens[idx + 2].c_str());
			material.diffuse.b = atof(tokens[idx + 3].c_str());
			material.diffuse.w = 1.0f;
			idx += 3;
		}
		else if (tokens[idx] == "*MATERIAL_SPECULAR")
		{
			material.specular.r = atof(tokens[idx + 1].c_str());
			material.specular.g = atof(tokens[idx + 2].c_str());
			material.specular.b = atof(tokens[idx + 3].c_str());
			material.specular.w = 1.0f;
			idx += 3;
		}
		else if (tokens[idx] == "*MATERIAL_SHINE")
		{
			float shine = atof(tokens[idx + 1].c_str());
			material.specular.w = shine;
			idx += 1;
		}
		else if (tokens[idx] == "*MATERIAL_TRANSPARENCY")
		{
			float transparent = atof(tokens[idx + 1].c_str());
			material.diffuse.w = 1 - transparent;
			idx += 1;
		}
		else if (tokens[idx] == "*MAP_DIFFUSE")
		{
			parseTexture(material);
		}
		else if (tokens[idx] == "*SUBMATERIAL")
		{
			idx += 3;
			parseMaterial();
		}

		idx++;
	}

	materials[name] = material;
}


void Converter::parseMesh()
{
	std::string name;
	AseMesh mesh;

	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*NODE_NAME")
		{
			name = tokens[idx + 1];
			idx += 1;
		}
		else if (tokens[idx] == "*NODE_TM")
		{
			while (tokens[idx] != "}")
			{
				idx++;
			}
		}
		else if (tokens[idx] == "*MESH")
		{
			idx += 2;
			parseMeshInfo(mesh);
		}

		idx++;
	}

	meshes[name] = mesh;
}

void Converter::parseTexture(AseMaterial& mat)
{
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*BITMAP")
		{
			mat.texture = tokens[idx + 1];
			idx += 1;
		}
		else if (tokens[idx] == "*UVW_U_TILING")
		{
			mat.uTile = atof(tokens[idx + 1].c_str());
			idx += 1;
		}
		else if (tokens[idx] == "*UVW_V_TILING")
		{
			mat.vTile = atof(tokens[idx + 1].c_str());
			idx += 1;
		}
		idx++;
	}
}

void Converter::parseMeshInfo(AseMesh& mesh)
{
	std::vector<AseFloat3> tVertices;
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MESH_VERTEX_LIST")
		{
			idx += 2;
			parseVertex(mesh);
		}
		else if (tokens[idx] == "*MESH_FACE_LIST")
		{
			idx += 2;
			parseFace(mesh);
		}
		else if (tokens[idx] == "*MESH_TVERTLIST")
		{
			idx += 2;
			parseTVertex(tVertices);
		}
		else if (tokens[idx] == "*MESH_TFACELIST")
		{
			idx += 2;
			parseTFace(mesh, tVertices);
		}
		else if (tokens[idx] == "*MESH_NORMALS")
		{
			idx += 2;
			parseNormal(mesh);
		}

		idx++;
	}
}

void Converter::parseVertex(AseMesh& mesh)
{
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MESH_VERTEX")
		{
			AseVertex vertex;

			vertex.pos.r = atof(tokens[idx + 2].c_str());
			vertex.pos.g = atof(tokens[idx + 4].c_str());
			vertex.pos.b = atof(tokens[idx + 3].c_str());
			idx += 4;
			mesh.vertices.push_back(vertex);
		}

		idx++;
	}
}

void Converter::parseFace(AseMesh& mesh)
{
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MESH_FACE")
		{
			mesh.indices.push_back(atoi(tokens[idx + 3].c_str()));
			mesh.indices.push_back(atoi(tokens[idx + 7].c_str()));
			mesh.indices.push_back(atoi(tokens[idx + 5].c_str()));
			idx += 17;
		}

		idx++;
	}
}

void Converter::parseTVertex(std::vector<AseFloat3>& tVertices)
{
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MESH_TVERT")
		{
			AseFloat3 vertex;

			vertex.r = atof(tokens[idx + 2].c_str());
			vertex.g = 1.0f - atof(tokens[idx + 3].c_str());

			tVertices.push_back(vertex);

			idx += 4;
		}
		idx++;
	}
}

void Converter::parseTFace(AseMesh& mesh, const std::vector<AseFloat3>& tVertices)
{
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MESH_TFACE")
		{
			int faceNum = atoi(tokens[idx + 1].c_str());

			mesh.vertices[mesh.indices[faceNum * 3]].texPos =
				tVertices[atoi(tokens[idx + 2].c_str())];

			mesh.vertices[mesh.indices[faceNum * 3 + 1]].texPos =
				tVertices[atoi(tokens[idx + 4].c_str())];

			mesh.vertices[mesh.indices[faceNum * 3 + 2]].texPos =
				tVertices[atoi(tokens[idx + 3].c_str())];

			idx += 4;
		}
		idx++;
	}
}

void Converter::parseNormal(AseMesh& mesh)
{
	while (tokens[idx] != "}")
	{
		if (tokens[idx] == "*MESH_VERTEXNORMAL")
		{
			auto& vertex = mesh.vertices[atoi(tokens[idx + 1].c_str())];

			vertex.normal.r += atof(tokens[idx + 2].c_str());
			vertex.normal.g += atof(tokens[idx + 4].c_str());
			vertex.normal.b += atof(tokens[idx + 3].c_str());

			idx += 4;
		}

		idx++;
	}
}
