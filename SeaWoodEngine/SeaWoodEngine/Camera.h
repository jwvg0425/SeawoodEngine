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

	const XMFLOAT4X4&	getView() const;

	CREATE_FUNC(Camera);
	static Camera*		createWithPos(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up);
protected:
	void				updateView();

	XMFLOAT4	m_EyePos;
	XMFLOAT4	m_TargetPos;
	XMFLOAT4	m_Up;
	XMFLOAT4X4	m_View;
};

NS_SW_END