#pragma once
#include "SeaWood.h"
#include "Ref.h"

NS_SW_BEGIN

class Camera;
class Renderer : public Ref
{
public:

	Renderer();
	virtual ~Renderer();

	virtual bool init();
	virtual void render();
	virtual void beginFrame();
	virtual void update(float dTime);

	void setBackgroundColor(const FLOAT colorRGBA[4]);
	void initRenderTarget();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	void setInputLayout(ID3D11InputLayout* inputLayout);
	void setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);
	void registerCamera(Camera* camera);
	void changeCamera(Camera* camera);
	Camera* getCamera();
	

	CREATE_FUNC(Renderer);

protected:

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
};

NS_SW_END