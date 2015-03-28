#pragma once
#include "SeaWood.h"
#include "Vertex.h"

NS_SW_BEGIN
class Node;
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

	template<typename Object>
	void updateByObject(Object* object);

protected:
	ID3DX11Effect* m_Fx = nullptr;
};

template<typename Object>
void SeaWood::Effect::updateByObject(Object* object)
{

}

class SimpleColorEffect : public Effect
{
public:
	using VertexType = Vertex::PosColor;

	SimpleColorEffect();
	~SimpleColorEffect() override;

	void setWorldViewProj(CXMMATRIX M);
	ID3DX11EffectTechnique* getTech() override;

	template<typename Object>
	void updateByObject(Object* object);

protected:
	ID3DX11EffectTechnique* m_Tech = nullptr;
	ID3DX11EffectMatrixVariable* m_FxWorldViewProj = nullptr;
};

template<typename Object>
void SeaWood::SimpleColorEffect::updateByObject(Object* object)
{
	auto world = object->getWorld();
	auto viewProj = GET_D3D_RENDERER()->getCamera()->getViewProj();
	auto worldViewProj = world * viewProj;
	setWorldViewProj(worldViewProj);
}

class Effects
{
public:
	static void destroyAll();

	static SimpleColorEffect* getSimpleColorEffect();
	
private:
	static SimpleColorEffect* m_SimpleColorFx;
};

NS_SW_END