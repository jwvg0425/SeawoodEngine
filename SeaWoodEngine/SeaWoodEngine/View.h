#pragma once
#include "SeaWood.h"
#include "Ref.h"

NS_SW_BEGIN

class View : public Ref
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

	virtual bool init() = 0;
	virtual void draw() = 0;
	virtual void beginFrame() = 0;
	virtual void update(float dTime);
	ViewType getType();

protected:

	ViewType m_Type = ViewType::NONE;
};

NS_SW_END