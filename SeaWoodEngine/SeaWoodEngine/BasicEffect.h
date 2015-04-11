#pragma once
#include "Effect.h"

NS_SW_BEGIN

class BasicEffect : public Effect
{
public:
	static const int LIGHT_NUM = 3;

	BasicEffect();
	~BasicEffect() override;

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
	void setDiffuseMap(ID3D11ShaderResourceView* tex);
	void setTexTransform(CXMMATRIX M);
	void setRimLight(bool useRimLight);

	void setFogStart(float start);
	void setFogRange(float range);
	void setFogEnable(bool enable);
	void setFogColor(const XMFLOAT4& v);

	ID3DX11EffectTechnique*	getTech() override;

	void updateByFrame() override;
	void updateByObject(Node* object) override;

protected:
	ID3DX11EffectTechnique*			m_Tech = nullptr;
	ID3DX11EffectTechnique*			m_TexTech = nullptr;
	ID3DX11EffectTechnique*			m_RimTech = nullptr;
	ID3DX11EffectTechnique*			m_TexRimTech = nullptr;

	ID3DX11EffectMatrixVariable*	m_WorldViewProj = nullptr;
	ID3DX11EffectMatrixVariable*	m_World = nullptr;
	ID3DX11EffectMatrixVariable*	m_WorldInvTranspose = nullptr;
	ID3DX11EffectVectorVariable*	m_EyePosW = nullptr;
	ID3DX11EffectMatrixVariable*	m_TexTransform = nullptr;
	ID3DX11EffectVariable*			m_DirLight = nullptr;
	ID3DX11EffectVariable*			m_PointLight = nullptr;
	ID3DX11EffectVariable*			m_SpotLight = nullptr;
	ID3DX11EffectVariable*			m_Material = nullptr;
	ID3DX11EffectVariable*			m_DirNum = nullptr;
	ID3DX11EffectVariable*			m_PointNum = nullptr;
	ID3DX11EffectVariable*			m_SpotNum = nullptr;

	//fog
	ID3DX11EffectVariable*			m_FogStart = nullptr;
	ID3DX11EffectVariable*			m_FogRange = nullptr;
	ID3DX11EffectVariable*			m_FogEnable = nullptr;
	ID3DX11EffectVectorVariable*	m_FogColor = nullptr;

	//texture
	ID3DX11EffectShaderResourceVariable* m_DiffuseMap = nullptr;

	bool							m_IsTexture = false;
	bool							m_UseRimLight = false;
};


NS_SW_END