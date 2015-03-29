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

	ID3D11ShaderResourceView* getTexture();
	void			setTexture(const std::wstring& fileName);
	void			setTextureTransform(CXMMATRIX matrix);
	XMFLOAT4X4		getTextureTransform();

protected:
	void updateWorld();

	//world를 구하기 위한 요소. 기본적으로 I.
	XMFLOAT4X4	m_Translation;
	XMFLOAT4X4	m_Scaling;
	XMFLOAT4X4	m_Rotation;
	XMFLOAT4X4	m_World;
	XMFLOAT4X4	m_TextureTransform;
	float m_X = 0.0f, m_Y = 0.0f, m_Z = 0.0f;
	float m_ScaleX = 0.0f, m_ScaleY = 0.0f, m_ScaleZ = 0.0f;
	float m_AngleX = 0.0f, m_AngleY = 0.0f, m_AngleZ = 0.0f;
	Material*	m_Material = nullptr;
	ID3D11ShaderResourceView* m_DiffuseMapSRV = nullptr;
};

NS_SW_END