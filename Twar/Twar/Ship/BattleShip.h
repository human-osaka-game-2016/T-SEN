#ifndef	BATTLESHIP_H
#define BATTLESHIP_H

#include "Ship.h"

class BattleShip : public Ship
{
private:
	virtual void Player();
	virtual void Ally();
	virtual void Enemy();

public:
	BattleShip(D3DXVECTOR3* pos);
	~BattleShip();
	virtual void Control();
	virtual void Draw();
};

#endif	//	BATTLESHIP_H