#pragma once
#include "Event.h"

NS_SW_BEGIN

struct MouseEvent : public Event
{
	enum Status
	{
		NONE = 0,
		LEFT = 1,
		RIGHT = 2,
		LEFT_RIGHT = 3
	};

	MouseEvent();
	~MouseEvent() override;

	Point2 m_Position = Point2::ZERO;
	Status m_Status = Status::NONE;
};

NS_SW_END