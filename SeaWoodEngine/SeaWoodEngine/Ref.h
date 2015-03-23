#include "SeaWood.h"

NS_SW_BEGIN

class Ref
{
public:
	Ref();
	virtual ~Ref();

	void retain();
	void release();
	void autorelease();

protected:
	int m_RefCount = 0;
};

NS_SW_END