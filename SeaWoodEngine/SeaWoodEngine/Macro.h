#define NS_SW_BEGIN namespace SeaWood{
#define NS_SW_END }
#define USING_NS_SW using namespace SeaWood
#define SAFE_DELETE(PTR)\
{\
	if (PTR != nullptr)\
	{\
		delete PTR; \
		PTR = nullptr; \
	}\
}
#define SAFE_RELEASE(PTR)\
{\
	if (PTR != nullptr)\
	{\
		PTR->release(); \
		PTR = nullptr; \
	}\
}
#define CREATE_FUNC(CLASS)\
CLASS* CLASS::create()\
{\
	CLASS* ptr = new CLASS; \
	ptr->incRefCount(); \
	return ptr; \
}