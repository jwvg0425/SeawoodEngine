#pragma once
#include "SeaWood.h"
#include "Light.h"
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

	virtual void updateByObject(Node* object);

protected:
	ID3DX11Effect* m_Fx = nullptr;
};

class SimpleColorEffect;
class SimpleLightEffect;
class BasicEffect;
class Effects final
{
public:
	static void destroyAll();
	static void beginFrame();

	static SimpleColorEffect*	getSimpleColorEffect();
	static SimpleLightEffect*	getSimpleLightEffect();
	static BasicEffect*			getBasicEffect();
	
private:
	static SimpleColorEffect*	m_SimpleColorFx;
	static SimpleLightEffect*	m_SimpleLightFx;
	static BasicEffect*			m_BasicFx;
};

NS_SW_END