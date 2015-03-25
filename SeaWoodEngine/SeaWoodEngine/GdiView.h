#include "View.h"

NS_SW_BEGIN

class GdiView : public View
{
public:
	GdiView();
	~GdiView() override;

	bool init() override;
	void beginFrame() override;
	void draw() override;

	HDC getDC();

	CREATE_FUNC(GdiView);

private:
	HBITMAP m_MemoryBitmap;
	HBITMAP m_OldBitmap;
	HDC		m_MemoryDC;
};

NS_SW_END