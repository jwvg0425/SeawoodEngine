#pragma once
#include "SeaWood.h"
#include "Light.h"
#include "Vertex.h"

NS_SW_BEGIN
class D3DNode;
class Effect
{
public:
	Effect(ID3D11Device* device, const std::wstring& filename);
	virtual ~Effect();

	Effect(const Effect& rhs) = delete;
	Effect& operator=(const Effect& rhs) = delete;
	ID3DX11Effect* getFx();
	virtual ID3DX11EffectTechnique* getTech() = 0;

	virtual void updateByFrame();

	virtual void updateByObject(D3DNode* object);

protected:
	ID3DX11Effect* m_Fx = nullptr;
};

class SimpleColorEffect : public Effect
{
public:
	using VertexType = Vertex::PosColor;

	SimpleColorEffect();
	~SimpleColorEffect() override;

	void setWorldViewProj(CXMMATRIX M);
	ID3DX11EffectTechnique* getTech() override;

	void updateByObject(D3DNode* object) override;

protected:
	ID3DX11EffectTechnique* m_Tech = nullptr;
	ID3DX11EffectMatrixVariable* m_FxWorldViewProj = nullptr;
};

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
	void setDirLight(const DirectionalLight& light);
	void setMaterial(const Material& mat);

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
	ID3DX11EffectVariable*			m_Material = nullptr;
};

class Effects
{
public:
	static void destroyAll();
	static void beginFrame();

	static SimpleColorEffect* getSimpleColorEffect();
	static SimpleLightEffect* getSimpleLightEffect();
	
private:
	static SimpleColorEffect* m_SimpleColorFx;
	static SimpleLightEffect* m_SimpleLightFx;
};

NS_SW_END