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
class BulletManager;

class Collision
{
private:
	D3DXVECTOR2 SubCheckSecondCollision(D3DXVECTOR2 a, D3DXVECTOR2 b);
	void CreateShipCollisionPos2D(D3DXVECTOR3 objPos, ShipManager::ShipSize shipSize, float rotate, D3DXVECTOR2* D3DXVECTOR2);
	void CreateShipCollisionPos3D(D3DXVECTOR3 objPos, ShipManager::ShipSize shipSize, float rotate, D3DXVECTOR3* D3DXVECTOR3);
	void CreateBulletCollisionPos3D(D3DXVECTOR3 objPos, BulletManager::BulletSize bulletSize, float rotate, D3DXVECTOR3* D3DXVECTOR3);
	void CreateMonsterCollisionPos3D(D3DXVECTOR3 objPos, MonsterManager::MonsterSize monsterSize, float rotate, D3DXVECTOR3* D3DXVECTOR3);
	D3DXVECTOR3 CreateNormalVector(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3);
	D3DXVECTOR3 InnerProduct(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);
	D3DXVECTOR3 CrossProduct(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);
	void CreateContactPoint(D3DXVECTOR3* pOut, D3DXVECTOR3* pPoint, D3DXVECTOR3* pNormal, D3DXVECTOR3* pVec1, D3DXVECTOR3* pVec2);
	bool IsPointInPolygon(D3DXVECTOR3* pPoint, D3DXVECTOR3* pPos1, D3DXVECTOR3* pPos2, D3DXVECTOR3* pPos3);
	D3DXVECTOR3* CreateVectorAtoB(D3DXVECTOR3* pOut, D3DXVECTOR3* pA, D3DXVECTOR3* pB);

public:
	Collision(ShipManager* a_pShipManager);
	~Collision();

	//	HasFirstHit とかに変えたい　がめんどくさい　後回しで
	bool CheckFirstCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float r1, float r2);
	bool CheckSecondCollisionShipShip(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, ShipManager::ShipSize shipSize1, ShipManager::ShipSize shipSize2, float rotate1, float rotate2);
	bool CheckSecondCollisionShipMonster(D3DXVECTOR3 shipPos, D3DXVECTOR3 monsterPos, ShipManager::ShipSize shipSize, MonsterManager::MonsterSize monsterSize, float shipRotate);
	bool CheckFirstCollision3D(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float r1, float r2);
	bool CheckSecondCollisionShipBullet(D3DXVECTOR3 shipPos, D3DXVECTOR3 oldBulletPos, D3DXVECTOR3 newBulletPos, ShipManager::ShipSize shipSize, BulletManager::BulletSize bulletSize, float shipRotate, float bulletRotate);
	bool CheckSecondCollisionMonsterBullet(D3DXVECTOR3 monsterPos, D3DXVECTOR3 oldBulletPos, D3DXVECTOR3 newBulletPos, MonsterManager::MonsterSize shipSize, BulletManager::BulletSize bulletSize, float monsterRotate, float bulletRotate);
};

#endif // COLLISION_H
