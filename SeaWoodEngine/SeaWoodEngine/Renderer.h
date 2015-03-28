#pragma once
#include "SeaWood.h"
#include "Ref.h"

NS_SW_BEGIN

class Renderer : public Ref
{
public:
	enum class ViewType
	{
		NONE = -1,
		D2_GDI,
		D3_DX
	};

	Renderer();
	virtual ~Renderer();

	virtual bool init() = 0;
	virtual void render() = 0;
	virtual void beginFrame() = 0;
	virtual void update(float dTime);
	ViewType getType();

protected:

	ViewType m_Type = ViewType::NONE;
};

NS_SW_END