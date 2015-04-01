#pragma once
#include "Effect.h"

NS_SW_BEGIN

class SimpleColorEffect : public Effect
{
public:

	SimpleColorEffect();
	~SimpleColorEffect() override;

	void setWorldViewProj(CXMMATRIX M);
	ID3DX11EffectTechnique* getTech() override;

	void updateByObject(D3DNode* object) override;

protected:
	ID3DX11EffectTechnique* m_Tech = nullptr;
	ID3DX11EffectMatrixVariable* m_FxWorldViewProj = nullptr;
};

NS_SW_END