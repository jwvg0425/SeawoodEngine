#include "SeaWood.h"

NS_SW_BEGIN

class View
{
public:
	enum class ViewType
	{
		NONE = -1,
		D2_GDI,
		D3_DX
	};

	View();
	virtual ~View();

	virtual void draw() = 0;
	virtual void beginFrame() = 0;

protected:

	ViewType m_Type = ViewType::NONE;
};

NS_SW_END