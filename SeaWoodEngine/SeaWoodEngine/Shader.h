#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

class Shader
{
public:
	Shader(const std::string& fileName, const std::string& techniqueName, const std::string& worldViewProjName,
		D3D11_INPUT_ELEMENT_DESC vertexDesc[], int vertexNum);
	virtual ~Shader();

	ID3DX11Effect*			getFx();
	ID3DX11EffectTechnique* getTech();
	ID3D11InputLayout*		getInputLayout();
	ID3DX11EffectMatrixVariable* getWorldViewProj();

private:
	void					buildFx(const std::string& fileName, const std::string& techniqueName, const std::string& worldViewProjName);
	void					buildVertexLayout(D3D11_INPUT_ELEMENT_DESC vertexDesc[], int vertexNum);

	ID3D11InputLayout*		m_InputLayout = nullptr;
	ID3DX11Effect*			m_Fx = nullptr;
	ID3DX11EffectTechnique* m_Tech = nullptr;
	ID3DX11EffectMatrixVariable* m_FxWorldViewProj = nullptr;
};

NS_SW_END