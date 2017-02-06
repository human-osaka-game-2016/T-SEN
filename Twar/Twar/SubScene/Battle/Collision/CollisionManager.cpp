/**
@file CollisionManager.cpp
@brief CollisionManagerクラス実装
@author kawaguchi
*/


#include "CollisionManager.h"
#include "Collision.h"
#include "../Monster/MonsterManager.h"

CollisionManager::CollisionManager(ShipManager* a_pShipManager, MonsterManager* a_pMonsterManager, BulletManager* a_pBulletManager)
	: m_pCollision(new Collision(a_pShipManager))
	, m_pShipManager(a_pShipManager)
	, m_pMonsterManager(a_pMonsterManager)
	, m_pBulletManager(a_pBulletManager)
{
	m_BattleShipSize = m_pShipManager->GetBattleShipSize();
	m_CruiserSize = m_pShipManager->GetCruiserSize();
	m_DestroyerSize = m_pShipManager->GetDestroyerSize();
	m_MonsterSize = m_pMonsterManager->GetMonsterSize();
}

CollisionManager::~CollisionManager()
{
	delete m_pCollision;
}

void CollisionManager::Control()
{
	float r1, r2;
	ShipManager::ShipSize shipSize1, shipSize2;

	for (int i = 0; i < m_pShipManager->GetArmyCount(); i++)
	{
		switch (m_pShipManager->GetArmyShipID(i))
		{
		case ShipManager::SHIP_ID::BATTLESHIP:
			r1 = m_BattleShipSize.m_MaxR;
			shipSize1 = m_BattleShipSize;
			break;
		case ShipManager::SHIP_ID::CRUISER:
			r1 = m_CruiserSize.m_MaxR;
			shipSize1 = m_CruiserSize;
			break;
		case ShipManager::SHIP_ID::DESTROYER:
			r1 = m_DestroyerSize.m_MaxR;
			shipSize1 = m_DestroyerSize;
			break;
		}
		
		for (int j = i + 1; j < m_pShipManager->GetArmyCount(); j++)
		{
			switch (m_pShipManager->GetArmyShipID(j))
			{
			case ShipManager::SHIP_ID::BATTLESHIP:
				r2 = m_BattleShipSize.m_MaxR;
				shipSize2 = m_BattleShipSize;
				break;
			case ShipManager::SHIP_ID::CRUISER:
				r2 = m_CruiserSize.m_MaxR;
				shipSize2 = m_CruiserSize;
				break;
			case ShipManager::SHIP_ID::DESTROYER:
				r2 = m_DestroyerSize.m_MaxR;
				shipSize2 = m_DestroyerSize;
				break;
			}

			if (m_pCollision->CheckFirstCollision(m_pShipManager->GetArmyObjPos(i), m_pShipManager->GetArmyObjPos(j), r1, r2))
			{
				if (m_pCollision->CheckSecondCollisionShipShip(m_pShipManager->GetArmyObjPos(i), m_pShipManager->GetArmyObjPos(j), shipSize1, shipSize2, m_pShipManager->GetArmyRotate(i), m_pShipManager->GetArmyRotate(j)))
				{
					m_pShipManager->SetArmyIsHit(i, true);
					m_pShipManager->SetArmyIsHit(j, true);
				}
			}
		}

		// モンスター増やすならマジックナンバーの0を変える必要あり
		if (m_pCollision->CheckFirstCollision(m_pShipManager->GetArmyObjPos(i), m_pMonsterManager->GetPos(0), r1, m_MonsterSize.m_MaxR))
		{
			if (m_pCollision->CheckSecondCollisionShipMonster(m_pShipManager->GetArmyObjPos(i), m_pMonsterManager->GetPos(0), shipSize1, m_MonsterSize, m_pShipManager->GetArmyRotate(i)))
			{
				m_pShipManager->SetArmyIsHit(i, true);
			}
		}

		for (int j = 0; j < m_pShipManager->GetEnemyCount(); j++)
		{
			switch (m_pShipManager->GetEnemyShipID(j))
			{
			case ShipManager::SHIP_ID::BATTLESHIP:
				r2 = m_BattleShipSize.m_MaxR;
				shipSize2 = m_BattleShipSize;
				break;
			case ShipManager::SHIP_ID::CRUISER:
				r2 = m_CruiserSize.m_MaxR;
				shipSize2 = m_CruiserSize;
				break;
			case ShipManager::SHIP_ID::DESTROYER:
				r2 = m_DestroyerSize.m_MaxR;
				shipSize2 = m_DestroyerSize;
				break;
			}

			if (m_pCollision->CheckFirstCollision(m_pShipManager->GetArmyObjPos(i), m_pShipManager->GetEnemyObjPos(j), r1, r2))
			{
				if (m_pCollision->CheckSecondCollisionShipShip(m_pShipManager->GetArmyObjPos(i), m_pShipManager->GetEnemyObjPos(j), shipSize1, shipSize2, m_pShipManager->GetArmyRotate(i), m_pShipManager->GetEnemyRotate(j)))
				{
					m_pShipManager->SetArmyIsHit(i, true);
					m_pShipManager->SetEnemyIsHit(j, true);
				}
			}

			for (int k = j + 1; k < m_pShipManager->GetEnemyCount(); k++)
			{
				switch (m_pShipManager->GetEnemyShipID(k))
				{
				case ShipManager::SHIP_ID::BATTLESHIP:
					r1 = m_BattleShipSize.m_MaxR;
					shipSize2 = m_BattleShipSize;
					break;
				case ShipManager::SHIP_ID::CRUISER:
					r1 = m_CruiserSize.m_MaxR;
					shipSize2 = m_CruiserSize;
					break;
				case ShipManager::SHIP_ID::DESTROYER:
					r1 = m_DestroyerSize.m_MaxR;
					shipSize2 = m_DestroyerSize;
					break;
				}

				if (m_pCollision->CheckFirstCollision(m_pShipManager->GetEnemyObjPos(k), m_pShipManager->GetEnemyObjPos(j), r1, r2))
				{
					if (m_pCollision->CheckSecondCollisionShipShip(m_pShipManager->GetEnemyObjPos(k), m_pShipManager->GetEnemyObjPos(j), shipSize1, shipSize2, m_pShipManager->GetEnemyRotate(k), m_pShipManager->GetEnemyRotate(j)))
					{
						m_pShipManager->SetEnemyIsHit(k, true);
						m_pShipManager->SetEnemyIsHit(j, true);
					}
				}
			}
		
			// モンスター増やすならマジックナンバーの0を変える必要あり
			if (m_pCollision->CheckFirstCollision(m_pShipManager->GetEnemyObjPos(j), m_pMonsterManager->GetPos(0), r1, m_MonsterSize.m_MaxR))
			{
				if (m_pCollision->CheckSecondCollisionShipMonster(m_pShipManager->GetEnemyObjPos(j), m_pMonsterManager->GetPos(0), shipSize1, m_MonsterSize ,m_pShipManager->GetEnemyRotate(j)))
				{
					m_pShipManager->SetEnemyIsHit(j, true);
				}
			}
		}
	}
}