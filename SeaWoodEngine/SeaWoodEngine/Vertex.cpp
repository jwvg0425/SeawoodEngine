#include "stdafx.h"
#include "Vertex.h"
#include "InputLayout.h"

ID3D11InputLayout* SeaWood::Vertex::PosColor::getInputLayout()
{
	return InputLayouts::getPosColor();
}

ID3D11InputLayout* SeaWood::Vertex::PosNormal::getInputLayout()
{
	return InputLayouts::getPosNormal();
}

ID3D11InputLayout* SeaWood::Vertex::PosBasic::getInputLayout()
{
	return InputLayouts::getPosBasic();
}
