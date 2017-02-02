/**
@file Collision.h
@brief Collisionクラスヘッダ
@author kawaguchi
*/

#ifndef COLLISION_H
#define COLLISION_H

#include <d3dx9.h>

class ShipManager;

class Collision
{
private:
	typedef struct COLLISIONPOSXY
	{
		float x, y;

	} CollisionPosXY;

	typedef struct COLLISIONPOSXYZ
	{
		float x, y, z;

	} CollisionPosXYZ;

	CollisionPosXY SubCheckSecondCollision(CollisionPosXY a, CollisionPosXY b);
	void Collision::CreateShipCollisionPos(D3DXVECTOR3 ShipCollisionPos, ShipManager::ShipSize shipSize, float rotate, CollisionPosXY* collisionPosXY);

public:
	Collision(ShipManager* a_pShipManager);
	~Collision();
	bool CheckFirstCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float r1, float r2);
	bool CheckSecondCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, ShipManager::ShipSize shipSize1, ShipManager::ShipSize shipSize2, float rotate1, float rotate2);
	//	bool CheckSecondCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, ShipManager::ShipSize shipSize1, Monster::MonsterSize monsterSize2);

};

#endif // COLLISION_H
