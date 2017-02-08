/**
@file Collision.h
@brief Collisionクラスヘッダ
@author kawaguchi
*/

#ifndef COLLISION_H
#define COLLISION_H

#include <d3dx9.h>

class ShipManager;
class MonsterManager;

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
	void Collision::CreateShipCollisionPos(D3DXVECTOR3 objPos, ShipManager::ShipSize shipSize, float rotate, CollisionPosXY* collisionPosXY);
	void Collision::CreateMonsterCollisionPos(D3DXVECTOR3 objPos, MonsterManager::MonsterSize monsterSize, float rotate, CollisionPosXY* collisionPosXY);

public:
	Collision(ShipManager* a_pShipManager);
	~Collision();
	bool CheckFirstCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float r1, float r2);
	bool CheckSecondCollisionShipShip(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, ShipManager::ShipSize shipSize1, ShipManager::ShipSize shipSize2, float rotate1, float rotate2);
	bool CheckSecondCollisionShipMonster(D3DXVECTOR3 shipPos, D3DXVECTOR3 monsterPos, ShipManager::ShipSize shipSize, MonsterManager::MonsterSize monsterSize, float shipRotate);

};

#endif // COLLISION_H
