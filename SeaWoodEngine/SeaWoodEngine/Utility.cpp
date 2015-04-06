#include "stdafx.h"
#include "Utility.h"
#include <fstream>

USING_NS_SW;

const float SeaWood::PI = 3.1415926535f;

void SeaWood::debugLogA(LPCSTR format, ...)
{
	char buf[1024];
	va_list marker;

	va_start(marker, format);
	vsprintf(buf, format, marker);

	strcat(buf, "\n");
	OutputDebugStringA(buf);
}

void SeaWood::debugLogW(LPCWSTR format, ...)
{
	wchar_t buf[1024];
	va_list marker;

	va_start(marker, format);
	vswprintf(buf, format, marker);

	wcscat(buf, L"\n");
	OutputDebugStringW(buf);
}

XMMATRIX SeaWood::inverseTranspose(CXMMATRIX M)
{
	// Inverse-transpose is just applied to normals.  So zero out 
	// translation row so that it doesn't get into our inverse-transpose
	// calculation--we don't want the inverse-transpose of the translation.
	XMMATRIX A = M;
	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	XMVECTOR det = XMMatrixDeterminant(A);
	return XMMatrixTranspose(XMMatrixInverse(&det, A));
}

void SeaWood::modelLoader(const std::string& fileName, ModelInfo& info)
{
	std::ifstream file;

	file.open(fileName, std::ios_base::in | std::ios_base::binary);

	if (!file.is_open())
	{
		return;
	}

	int size;

	file.read((char*)&size, sizeof(size_t));

	for (int i = 0; i < size; i++)
	{
		Vertex::PosBasic vertex;

		file.read((char*)&vertex.m_Pos.x, sizeof(float));
		file.read((char*)&vertex.m_Pos.y, sizeof(float));
		file.read((char*)&vertex.m_Pos.z, sizeof(float));

		file.read((char*)&vertex.m_Normal.x, sizeof(float));
		file.read((char*)&vertex.m_Normal.y, sizeof(float));
		file.read((char*)&vertex.m_Normal.z, sizeof(float));

		file.read((char*)&vertex.m_Tex.x, sizeof(float));
		file.read((char*)&vertex.m_Tex.y, sizeof(float));

		info.m_Vertices.push_back(vertex);
	}

	file.read((char*)&size, sizeof(size_t));

	for (int i = 0; i < size; i++)
	{
		UINT idx;

		file.read((char*)&idx, sizeof(unsigned));

		info.m_Indices.push_back(idx);
	}

	file.read((char*)&info.m_Material.m_Ambient.x, sizeof(float));
	file.read((char*)&info.m_Material.m_Ambient.y, sizeof(float));
	file.read((char*)&info.m_Material.m_Ambient.z, sizeof(float));
	file.read((char*)&info.m_Material.m_Ambient.w, sizeof(float));

	file.read((char*)&info.m_Material.m_Diffuse.x, sizeof(float));
	file.read((char*)&info.m_Material.m_Diffuse.y, sizeof(float));
	file.read((char*)&info.m_Material.m_Diffuse.z, sizeof(float));
	file.read((char*)&info.m_Material.m_Diffuse.w, sizeof(float));

	file.read((char*)&info.m_Material.m_Specular.x, sizeof(float));
	file.read((char*)&info.m_Material.m_Specular.y, sizeof(float));
	file.read((char*)&info.m_Material.m_Specular.z, sizeof(float));
	file.read((char*)&info.m_Material.m_Specular.w, sizeof(float));

	file.read((char*)&info.m_UTile, sizeof(float));
	file.read((char*)&info.m_VTile, sizeof(float));

	file.read((char*)&size, sizeof(size_t));

	char buffer[512];

	file.read(buffer, sizeof(char)*size);

	buffer[size] = '\0';

	info.m_Texture = buffer;
}
