#ifndef	DESTROYER_H
#define DESTROYER_H

#include "Ship.h"

class Destroyer : public Ship
{
private:
	virtual void Player();
	virtual void Ally();
	virtual void Enemy();

public:
	Destroyer(D3DXVECTOR3* pos);
	~Destroyer();
	virtual void Control();
	virtual void Draw();
};

#endif	//	DESTROYER_H