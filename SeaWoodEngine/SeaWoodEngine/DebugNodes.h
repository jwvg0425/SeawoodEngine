#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

enum class DebugMode
{
	NONE = 0,
	PRINT_AXIS = 1
};

class Node;
class DebugNodes
{
public:
	static void destroyAll();

	static Node* getDebugNode(DebugMode mode);
private:
	static void createAxis();
};

NS_SW_END