#include "Renderer.h"

NS_SW_BEGIN

class GdiRenderer : public Renderer
{
public:
	GdiRenderer();
	~GdiRenderer() override;

	bool init() override;
	void beginFrame() override;
	void draw() override;

	HDC getDC();

	CREATE_FUNC(GdiRenderer);

private:
	HBITMAP m_MemoryBitmap;
	HBITMAP m_OldBitmap;
	HDC		m_MemoryDC;
};

NS_SW_END