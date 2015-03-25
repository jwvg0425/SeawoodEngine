#pragma once
#include "View.h"

NS_SW_BEGIN

class Camera;
class D3DView : public View
{
public:
	D3DView();
	~D3DView() override;

	bool init() override;
	void beginFrame() override;
	void draw() override;
	void setBackgroundColor(const FLOAT colorRGBA[4]);
	void setProjection(FLOAT fovAngleY, FLOAT nearZ, FLOAT farZ);
	void initRenderTarget();
	const XMFLOAT4X4& getViewProj();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	void setInputLayout(ID3D11InputLayout* inputLayout);
	void setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);
	void registerCamera(Camera* camera);

	CREATE_FUNC(D3DView);

private:
	static const float PI;

	void updateProjection();

	ID3D11Device* m_D3DDevice = nullptr;
	ID3D11DeviceContext* m_D3DImmediateContext = nullptr;
	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11Texture2D* m_DepthStencilBuffer = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	D3D11_VIEWPORT m_ScreenViewport;
	D3D_DRIVER_TYPE m_D3DDriverType = D3D_DRIVER_TYPE_HARDWARE;
	bool m_IsEnable4xMsaa = true;
	UINT m_4xMsaaQuality;
	
	FLOAT m_BackgroundColor[4];

	Camera* m_Camera = nullptr;

	XMFLOAT4X4 m_Projection;
	XMFLOAT4X4 m_ViewProj;

	FLOAT m_FovAngleY;
	FLOAT m_Near;
	FLOAT m_Far;

};

NS_SW_END