/**
@file CollisionManager.h
@brief CollisionManagerクラスヘッダ
@author kawaguchi
*/

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "../Ship/ShipManager.h"

class Collision;
class ShipManager;
class MonsterManager;
class BulletManager;

class CollisionManager
{
public:
	CollisionManager(ShipManager* a_pShipManager, MonsterManager* a_pMonsterManager, BulletManager* a_pBulletManager);
	~CollisionManager();
	void Control();
private:
	Collision*		m_pCollision;
	ShipManager*	m_pShipManager;
	MonsterManager*	m_pMonsterManager;
	BulletManager*	m_pBulletManager;
	ShipManager::ShipSize m_BattleShipSize;
	ShipManager::ShipSize m_CruiserSize;
	ShipManager::ShipSize m_DestroyerSize;
};

#endif // COLLISIONMANAGER_H
