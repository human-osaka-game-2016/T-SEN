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
}

CollisionManager::~CollisionManager()
{
	delete m_pCollision;
}

void CollisionManager::Control()
{
	for (int i = 0; i < m_pShipManager->GetArmyCount(); i++)
	{
		for (int j = i + 1; j < m_pShipManager->GetArmyCount(); j++)
		{
			float r1, r2;
			ShipManager::ShipSize shipSize1, shipSize2;

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
				if (m_pCollision->CheckSecondCollision(m_pShipManager->GetArmyObjPos(i), m_pShipManager->GetArmyObjPos(j), shipSize1, shipSize2, m_pShipManager->GetArmyRotate(i), m_pShipManager->GetArmyRotate(j)))
				{
					m_pShipManager->SetArmyIsHit(i, true);
					m_pShipManager->SetArmyIsHit(j, true);
				}
			}
		}
	

		for (int j = 0; j < m_pShipManager->GetEnemyCount(); j++)
		{
			float r1, r2;
			ShipManager::ShipSize shipSize1, shipSize2;

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
				if (m_pCollision->CheckSecondCollision(m_pShipManager->GetArmyObjPos(i), m_pShipManager->GetEnemyObjPos(j), shipSize1, shipSize2, m_pShipManager->GetArmyRotate(i), m_pShipManager->GetEnemyRotate(j)))
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

				if (m_pCollision->CheckFirstCollision(m_pShipManager->GetEnemyObjPos(i), m_pShipManager->GetEnemyObjPos(j), r1, r2))
				{
					if (m_pCollision->CheckSecondCollision(m_pShipManager->GetEnemyObjPos(i), m_pShipManager->GetEnemyObjPos(j), shipSize1, shipSize2, m_pShipManager->GetEnemyRotate(i), m_pShipManager->GetEnemyRotate(j)))
					{
						m_pShipManager->SetEnemyIsHit(i, true);
						m_pShipManager->SetEnemyIsHit(j, true);
					}
				}
			}
		}
	}
}