#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

struct Event
{
	Event();
	virtual ~Event();
};

enum class EventType
{
	NONE,
	MOUSE_DOWN,
	MOUSE_MOVE,
	MOUSE_UP,
	UPDATE_FRAME,
	PICK_TRIANGLE,
};

NS_SW_END