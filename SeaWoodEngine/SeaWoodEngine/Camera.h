#pragma once
#include "Node.h"

NS_SW_BEGIN

//3D World에서 플레이어가 보는 방향을 설정.
class Camera : public Node
{
public:
	Camera();
	Camera(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up);
	virtual ~Camera();

	bool				init() override;

	void				setEyePos(XMVECTOR eyePos);
	void				setUpVector(XMVECTOR up);
	void				setLens(FLOAT fovAngleY, FLOAT aspect, FLOAT nearZ, FLOAT farZ);

	XMMATRIX			getView() const;
	XMMATRIX			getProjection() const;
	XMMATRIX			getViewProj() const;

	XMFLOAT3			getEyePos();
	
	XMVECTOR			getLookVector();

	void				walk(float d);
	void				strafe(float d);
	void				pitch(float angle);
	void				rotateY(float angle);

	CREATE_FUNC(Camera);
	static Camera*		createWithPos(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up);

protected:
	void		updateView();
	void		updateProjection();

	XMFLOAT3	m_Pos;
	XMFLOAT3	m_Right; //x
	XMFLOAT3	m_Up; //y
	XMFLOAT3	m_Look; //z
	XMFLOAT4X4	m_View;
	XMFLOAT4X4	m_Projection;
	FLOAT		m_FovAngleY = 0.0f;
	FLOAT		m_Aspect = 0.0f;
	FLOAT		m_NearZ = 0.0f;
	FLOAT		m_FarZ = 0.0f;
};

NS_SW_END