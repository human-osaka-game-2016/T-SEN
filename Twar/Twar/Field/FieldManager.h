#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include"Ocene.h"
#include"Sky.h"

class FieldManager
{
private:
	Ocene*   m_Ocene;
	Sky*     m_Sky;

public:
	FieldManager();
	~FieldManager();
	void Control();
	void Draw();
};
#endif
