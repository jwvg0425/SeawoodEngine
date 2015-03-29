#pragma once
#include "Effect.h"

NS_SW_BEGIN

class SimpleLightEffect : public Effect
{
public:
	using VertexType = Vertex::PosNormal;

	SimpleLightEffect();
	~SimpleLightEffect() override;

	void setWorldViewProj(CXMMATRIX M);
	void setWorld(CXMMATRIX M);
	void setWorldInvTranspose(CXMMATRIX M);
	void setEyePosW(const XMFLOAT3& v);
	void setDirLight(DirectionalLight* light);
	void setPointLight(PointLight* light);
	void setSpotLight(SpotLight* light);
	void setMaterial(const Material& mat);
	void setDirLightNum(int n);
	void setPointLightNum(int n);
	void setSpotLightNum(int n);

	ID3DX11EffectTechnique*			getTech() override;

	void updateByFrame() override;
	void updateByObject(D3DNode* object) override;

protected:
	ID3DX11EffectTechnique*			m_Tech = nullptr;

	ID3DX11EffectMatrixVariable*	m_WorldViewProj = nullptr;
	ID3DX11EffectMatrixVariable*	m_World = nullptr;
	ID3DX11EffectMatrixVariable*	m_WorldInvTranspose = nullptr;
	ID3DX11EffectVectorVariable*	m_EyePosW = nullptr;
	ID3DX11EffectVariable*			m_DirLight = nullptr;
	ID3DX11EffectVariable*			m_PointLight = nullptr;
	ID3DX11EffectVariable*			m_SpotLight = nullptr;
	ID3DX11EffectVariable*			m_Material = nullptr;
	ID3DX11EffectVariable*			m_DirNum = nullptr;
	ID3DX11EffectVariable*			m_PointNum = nullptr;
	ID3DX11EffectVariable*			m_SpotNum = nullptr;
};


NS_SW_END