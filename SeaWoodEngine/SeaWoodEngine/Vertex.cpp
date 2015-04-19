#include "stdafx.h"
#include "Vertex.h"
#include "InputLayout.h"
#include "Effects.h"
#include "SimpleColorEffect.h"
#include "SimpleLightEffect.h"
#include "BasicEffect.h"

USING_NS_SW;

ID3D11InputLayout* SeaWood::Vertex::PosColor::getInputLayout()
{
	return InputLayouts::getPosColor();
}

Vertex::PosColor::EffectType SeaWood::Vertex::PosColor::getDefaultEffect()
{
	return Effects::getSimpleColorEffect();
}

ID3D11InputLayout* SeaWood::Vertex::PosNormal::getInputLayout()
{
	return InputLayouts::getPosNormal();
}

Vertex::PosNormal::EffectType SeaWood::Vertex::PosNormal::getDefaultEffect()
{
	return Effects::getSimpleLightEffect();
}

ID3D11InputLayout* SeaWood::Vertex::PosBasic::getInputLayout()
{
	return InputLayouts::getPosBasic();
}

Vertex::PosBasic::EffectType SeaWood::Vertex::PosBasic::getDefaultEffect()
{
	return Effects::getBasicEffect();
}
