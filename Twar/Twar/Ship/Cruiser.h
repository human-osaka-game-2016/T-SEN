#ifndef	CRUISER_H
#define CRUISER_H

#include "Ship.h"

class Cruiser : public Ship
{
private:
	virtual void Player();
	virtual void Ally();
	virtual void Enemy();

public:
	Cruiser(D3DXVECTOR3* pos);
	~Cruiser();
	virtual void Control();
	virtual void Draw();
};

#endif	//	CRUISER_H