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
	void				setTargetPos(XMVECTOR targetPos);
	void				setUpVector(XMVECTOR up);
	void				setLens(FLOAT fovAngleY, FLOAT aspect, FLOAT nearZ, FLOAT farZ);

	XMMATRIX			getView() const;
	XMMATRIX			getProjection() const;
	XMMATRIX			getViewProj() const;

	XMFLOAT3			getEyePosW();

	XMVECTOR			getTarget();

	CREATE_FUNC(Camera);
	static Camera*		createWithPos(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up);

protected:
	void		updateView();
	void		updateProjection();

	XMFLOAT4	m_EyePos;
	XMFLOAT4	m_TargetPos;
	XMFLOAT4	m_Up;
	XMFLOAT4X4	m_View;
	XMFLOAT4X4	m_Projection;
	FLOAT		m_FovAngleY = 0.0f;
	FLOAT		m_Aspect = 0.0f;
	FLOAT		m_NearZ = 0.0f;
	FLOAT		m_FarZ = 0.0f;
};

NS_SW_END