#pragma once
#include "Node.h"
#include "Light.h"

NS_SW_BEGIN

class D3DNode : public Node
{
public:
	D3DNode();
	~D3DNode() override;

	bool init() override;

	void setPosition(float x, float y, float z, bool relative = false);
	void setScale(float x, float y, float z, bool relative = false);
	void setRotate(float x, float y, float z, bool relative = false);

	//포인터로 넘어온 변수에 해당하는 값 저장해서 돌려줌
	void getPosition(float* x, float* y, float* z);
	void getScale(float* scaleX, float* scaleY, float* scaleZ);
	void getRotate(float* angleX, float* angleY, float* angleZ);

	XMMATRIX getWorld();

	const Material*	getMaterial();
	void			setMaterial(Material material);

protected:
	void updateWorld();

	//world를 구하기 위한 요소. 기본적으로 I.
	XMFLOAT4X4	m_Translation;
	XMFLOAT4X4	m_Scaling;
	XMFLOAT4X4	m_Rotation;
	XMFLOAT4X4	m_World;
	float m_X, m_Y, m_Z;
	float m_ScaleX, m_ScaleY, m_ScaleZ;
	float m_AngleX, m_AngleY, m_AngleZ;
	Material*	m_Material = nullptr;
};

NS_SW_END