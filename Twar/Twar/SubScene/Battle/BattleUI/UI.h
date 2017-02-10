#ifndef UI_H
#define UI_H

#include <d3dx9.h>

class UI
{

public:
	UI();
	virtual ~UI();
	virtual void Control() = 0;
	virtual void Draw() = 0;

protected:
	D3DXVECTOR2			m_Pos;
	float				m_Angle;

};

#endif

