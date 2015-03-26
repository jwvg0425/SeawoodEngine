#include "stdafx.h"
#include "Shader.h"
#include "Director.h"
#include "D3DRenderer.h"
#include <fstream>

USING_NS_SW;

Shader::Shader(const std::string& fileName, const std::string& techniqueName, const std::string& worldViewProjName,
	D3D11_INPUT_ELEMENT_DESC vertexDesc[], int vertexNum)
{
	buildFx(fileName, techniqueName, worldViewProjName);
	buildVertexLayout(vertexDesc, vertexNum);
}

Shader::~Shader()
{
	ReleaseCOM(m_InputLayout);
	ReleaseCOM(m_Fx);
}

void Shader::buildFx(const std::string& fileName, const std::string& techniqueName, const std::string& worldViewProjName)
{
	std::ifstream fin(fileName, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 0, GET_D3D_RENDERER()->getDevice(), &m_Fx));
	
	m_Tech = m_Fx->GetTechniqueByName(techniqueName.c_str());
	m_FxWorldViewProj = m_Fx->GetVariableByName(worldViewProjName.c_str())->AsMatrix();

}

void Shader::buildVertexLayout(D3D11_INPUT_ELEMENT_DESC vertexDesc[], int vertexNum)
{
	D3DX11_PASS_DESC passDesc;

	m_Tech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(GET_D3D_RENDERER()->getDevice()->
		CreateInputLayout(vertexDesc, vertexNum, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &m_InputLayout));
}

ID3DX11Effect* SeaWood::Shader::getFx()
{
	return m_Fx;
}

ID3D11InputLayout* SeaWood::Shader::getInputLayout()
{
	return m_InputLayout;
}

ID3DX11EffectTechnique* SeaWood::Shader::getTech()
{
	return m_Tech;
}

ID3DX11EffectMatrixVariable* SeaWood::Shader::getWorldViewProj()
{
	return m_FxWorldViewProj;
}
