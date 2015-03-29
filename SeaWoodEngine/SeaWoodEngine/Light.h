#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

//평행광
struct DirectionalLight
{
	DirectionalLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 m_Ambient;
	XMFLOAT4 m_Diffuse;
	XMFLOAT4 m_Specular;
	XMFLOAT3 m_Direction;
	float m_Pad; // Pad the last float so we can set an array of lights if we wanted.
};

//점광
struct PointLight
{
	PointLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 m_Ambient;
	XMFLOAT4 m_Diffuse;
	XMFLOAT4 m_Specular;

	// Packed into 4D vector: (Position, Range)
	XMFLOAT3 m_Position;
	float m_Range;

	// Packed into 4D vector: (A0, A1, A2, Pad)
	XMFLOAT3 m_Att;
	float m_Pad; // Pad the last float so we can set an array of lights if we wanted.
};

//점적광
struct SpotLight
{
	SpotLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 m_Ambient;
	XMFLOAT4 m_Diffuse;
	XMFLOAT4 m_Specular;

	// Packed into 4D vector: (Position, Range)
	XMFLOAT3 m_Position;
	float m_Range;

	// Packed into 4D vector: (Direction, Spot)
	XMFLOAT3 m_Direction;
	float m_Spot;

	// Packed into 4D vector: (Att, Pad)
	XMFLOAT3 m_Att;
	float m_Pad; // Pad the last float so we can set an array of lights if we wanted.
};
//재질 설정
struct Material
{
	Material() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 m_Ambient;
	XMFLOAT4 m_Diffuse;
	XMFLOAT4 m_Specular; // w = SpecPower
	XMFLOAT4 m_Reflect;
};

NS_SW_END