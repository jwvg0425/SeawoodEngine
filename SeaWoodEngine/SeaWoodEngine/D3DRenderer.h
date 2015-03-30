#pragma once
#include "Renderer.h"

NS_SW_BEGIN

enum class RasterizerType
{
	TRANSPARENCY
};

class Camera;
class D3DRenderer : public Renderer
{
public:
	D3DRenderer();
	~D3DRenderer() override;

	bool init() override;
	void beginFrame() override;
	void render() override;
	void setBackgroundColor(const FLOAT colorRGBA[4]);
	void initRenderTarget();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	void setInputLayout(ID3D11InputLayout* inputLayout);
	void setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);
	void registerCamera(Camera* camera);
	void changeCamera(Camera* camera);
	Camera* getCamera();
	void update(float dTime) override;

	CREATE_FUNC(D3DRenderer);

private:

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