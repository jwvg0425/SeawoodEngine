#pragma once

NS_SW_BEGIN

class Node;
class Director
{
public:
	static Director*	getInstance();
	static void			releaseInstance();

	void				gameLoop();

protected:
	Director();
	~Director();
	static Director*	m_Instance;
};

NS_SW_END