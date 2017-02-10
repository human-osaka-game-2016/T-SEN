/**
@file CollisionManager.h
@brief CollisionManagerクラスヘッダ
@author kawaguchi
*/

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "../Ship/ShipManager.h"
#include "../Monster/MonsterManager.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/AIBulletManager.h"
#include "../Monster/MonsterBullet/MonsterBulletManager.h"

class Collision;
class ShipManager;
class MonsterManager;
class BulletManager;
class AIBulletManager;
class MonsterBulletManager;

class CollisionManager
{
public:
	CollisionManager(ShipManager* a_pShipManager, MonsterManager* a_pMonsterManager, BulletManager* a_pBulletManager, AIBulletManager* a_pAIBulletManager, MonsterBulletManager* a_pMonsterBulletManager);
	~CollisionManager();
	void Control();
private:
	Collision*		m_pCollision;
	ShipManager*	m_pShipManager;
	MonsterManager*	m_pMonsterManager;
	BulletManager*	m_pBulletManager;
	AIBulletManager* m_pAIBulletManager;
	MonsterBulletManager* m_pMonsterBulletManager;
	ShipManager::ShipSize m_BattleShipSize;
	ShipManager::ShipSize m_CruiserSize;
	ShipManager::ShipSize m_DestroyerSize;
	MonsterManager::MonsterSize m_MonsterSize;
	BulletManager::BulletSize m_BulletSize;
	MonsterBulletManager::MonsterBulletSize m_MonsterBulletSize;
};

#endif // COLLISIONMANAGER_H

