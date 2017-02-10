/**
@file CollisionManager.cpp
@brief CollisionManagerクラス実装
@author kawaguchi
*/


#include "CollisionManager.h"
#include "Collision.h"

CollisionManager::CollisionManager(ShipManager* a_pShipManager, MonsterManager* a_pMonsterManager, BulletManager* a_pBulletManager, AIBulletManager* a_pAIBulletManager, MonsterBulletManager* a_pMonsterBulletManager)
	: m_pCollision(new Collision(a_pShipManager))
	, m_pShipManager(a_pShipManager)
	, m_pMonsterManager(a_pMonsterManager)
	, m_pBulletManager(a_pBulletManager)
	, m_pAIBulletManager(a_pAIBulletManager)
	, m_pMonsterBulletManager(a_pMonsterBulletManager)
{
	m_BattleShipSize = m_pShipManager->GetBattleShipSize();
	m_CruiserSize = m_pShipManager->GetCruiserSize();
	m_DestroyerSize = m_pShipManager->GetDestroyerSize();
	m_MonsterSize = m_pMonsterManager->GetMonsterSize();
	m_BulletSize = m_pBulletManager->GetBulletSize();
	m_MonsterBulletSize = m_pMonsterBulletManager->GetMonsterBulletSize();
}

CollisionManager::~CollisionManager()
{
	delete m_pCollision;
}

void CollisionManager::Control()
{
	float r1, r2;
	ShipManager::ShipSize shipSize1, shipSize2;
	int BulletCount = m_pBulletManager->GetBulletCount();
	int AIBulletCount = m_pAIBulletManager->GetBulletCount();
	int MonsterBulletCount = m_pMonsterBulletManager->GetBulletCount();

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
		
		for (int j = 0; j < m_pShipManager->GetArmyCount(); j++)
		{
			if (i != j)
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
		}

		// モンスター増やすならマジックナンバーの0を変える必要あり
		if (m_pCollision->CheckFirstCollision(m_pShipManager->GetArmyObjPos(i), m_pMonsterManager->GetPos(0), r1, m_MonsterSize.m_MaxR * 1.5f))
		{
			if (m_pCollision->CheckSecondCollisionShipMonster(m_pShipManager->GetArmyObjPos(i), m_pMonsterManager->GetPos(0), shipSize1, m_MonsterSize, m_pShipManager->GetArmyRotate(i)))
			{
				m_pShipManager->SetArmyIsHit(i, true);
			}
		}
		
		for (int j = 0; j < BulletCount; j++)
		{
			if (m_pCollision->CheckFirstCollision3D(m_pShipManager->GetArmyObjPos(i), m_pBulletManager->GetBulletPos(j), r1, m_BulletSize.m_MaxR))
			{
				if (m_pCollision->CheckSecondCollisionShipBullet(m_pShipManager->GetArmyObjPos(i),
																 m_pBulletManager->GetBulletOldPos(j),
																 m_pBulletManager->GetBulletPos(j),
																 shipSize1,
																 m_BulletSize,
																 m_pShipManager->GetArmyRotate(i),
																 m_pBulletManager->GetBulletRotate(j)))
				{
					m_pBulletManager->SetHit(j, true);
				}
			}
		}

		for (int j = 0; j < AIBulletCount; j++)
		{
			if (m_pCollision->CheckFirstCollision3D(m_pShipManager->GetArmyObjPos(i), m_pAIBulletManager->GetBulletPos(j), r1, m_BulletSize.m_MaxR))
			{
				if (m_pCollision->CheckSecondCollisionShipBullet(m_pShipManager->GetArmyObjPos(i),
																 m_pAIBulletManager->GetBulletOldPos(j),
																 m_pAIBulletManager->GetBulletPos(j),
																 shipSize1,
																 m_BulletSize,
																 m_pShipManager->GetArmyRotate(i),
																 m_pAIBulletManager->GetBulletAngle(j)))
				{
					m_pAIBulletManager->SetHit(j, true);
				}
			}
		}

		for (int j = 0; j < MonsterBulletCount; j++)
		{
			if (m_pCollision->CheckFirstCollision3D(m_pShipManager->GetArmyObjPos(i), m_pMonsterBulletManager->GetBulletPos(j), r1 * 0.9f, m_MonsterBulletSize.m_MaxR * 0.5f))
			{
				if (m_pCollision->CheckSecondCollisionShipBullet(m_pShipManager->GetArmyObjPos(i),
																 m_pMonsterBulletManager->GetBulletOldPos(j),
																 m_pMonsterBulletManager->GetBulletPos(j),
																 shipSize1,
																 m_BulletSize,
																 m_pShipManager->GetArmyRotate(i),
																 m_pMonsterBulletManager->GetBulletAngle(j)))
				{
					m_pMonsterBulletManager->SetHit(j, true);
				}
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
				if (j != k)
				{
					switch (m_pShipManager->GetEnemyShipID(k))
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

					if (m_pCollision->CheckFirstCollision(m_pShipManager->GetEnemyObjPos(k), m_pShipManager->GetEnemyObjPos(j), r1, r2))
					{
						if (m_pCollision->CheckSecondCollisionShipShip(m_pShipManager->GetEnemyObjPos(k), m_pShipManager->GetEnemyObjPos(j), shipSize1, shipSize2, m_pShipManager->GetEnemyRotate(k), m_pShipManager->GetEnemyRotate(j)))
						{
							m_pShipManager->SetEnemyIsHit(k, true);
							m_pShipManager->SetEnemyIsHit(j, true);
						}
					}
				}
			}
		
			// モンスター増やすならマジックナンバーの0を変える必要あり
			if (m_pCollision->CheckFirstCollision(m_pShipManager->GetEnemyObjPos(j), m_pMonsterManager->GetPos(0), r2, m_MonsterSize.m_MaxR * 1.5f))
			{
				if (m_pCollision->CheckSecondCollisionShipMonster(m_pShipManager->GetEnemyObjPos(j), m_pMonsterManager->GetPos(0), shipSize2, m_MonsterSize ,m_pShipManager->GetEnemyRotate(j)))
				{
					m_pShipManager->SetEnemyIsHit(j, true);
				}
			}

			for (int k = 0; k < BulletCount; k++)
			{
				if (m_pCollision->CheckFirstCollision3D(m_pShipManager->GetEnemyObjPos(j), m_pBulletManager->GetBulletPos(k), r2, m_BulletSize.m_MaxR))
				{
					if (m_pCollision->CheckSecondCollisionShipBullet(m_pShipManager->GetEnemyObjPos(j),
																	 m_pBulletManager->GetBulletOldPos(k),
																	 m_pBulletManager->GetBulletPos(k),
																	 shipSize2,
																	 m_BulletSize,
																	 m_pShipManager->GetEnemyRotate(j),
																	 m_pBulletManager->GetBulletRotate(k)))
					{
						m_pBulletManager->SetHit(k, true);
					}
				}
			}

			for (int k = 0; k < AIBulletCount; k++)
			{
				if (m_pCollision->CheckFirstCollision3D(m_pShipManager->GetEnemyObjPos(j), m_pAIBulletManager->GetBulletPos(k), r2, m_BulletSize.m_MaxR))
				{
					if (m_pCollision->CheckSecondCollisionShipBullet(m_pShipManager->GetEnemyObjPos(j),
																	 m_pAIBulletManager->GetBulletOldPos(k),
																	 m_pAIBulletManager->GetBulletPos(k),
																	 shipSize2,
																	 m_BulletSize,
																	 m_pShipManager->GetEnemyRotate(j),
																	 m_pAIBulletManager->GetBulletAngle(k)))
					{
						m_pAIBulletManager->SetHit(k, true);
					}
				}
			}

			for (int k = 0; k < MonsterBulletCount; k++)
			{
				if (m_pCollision->CheckFirstCollision3D(m_pShipManager->GetEnemyObjPos(j), m_pMonsterBulletManager->GetBulletPos(k), r2 * 0.9f, m_MonsterBulletSize.m_MaxR * 0.5f))
				{
					if (m_pCollision->CheckSecondCollisionShipBullet(m_pShipManager->GetEnemyObjPos(j),
																	 m_pMonsterBulletManager->GetBulletOldPos(k),
																	 m_pMonsterBulletManager->GetBulletPos(k),
																	 shipSize2,
																	 m_BulletSize,
																	 m_pShipManager->GetEnemyRotate(j),
																	 m_pMonsterBulletManager->GetBulletAngle(k)))
					{
						m_pMonsterBulletManager->SetHit(k, true);
					}
				}
			}
		}
	}

	for (int i = 0; i < BulletCount; i++)
	{
		if (m_pCollision->CheckFirstCollision3D(m_pMonsterManager->GetPos(0), m_pBulletManager->GetBulletPos(i), m_MonsterSize.m_MaxR * 1.5f, m_BulletSize.m_MaxR))
		{
			if (m_pCollision->CheckSecondCollisionMonsterBullet(m_pMonsterManager->GetPos(0),
																m_pBulletManager->GetBulletOldPos(i),
																m_pBulletManager->GetBulletPos(i),
																m_MonsterSize,
																m_BulletSize,
																m_pMonsterManager->GetAngle(0),
																m_pBulletManager->GetBulletRotate(i)))
			{
				m_pBulletManager->SetHit(i, true);
			}
		}
	}
	for (int i = 0; i < AIBulletCount; i++)
	{
		if (m_pCollision->CheckFirstCollision3D(m_pMonsterManager->GetPos(0), m_pAIBulletManager->GetBulletPos(i), m_MonsterSize.m_MaxR * 1.5f, m_BulletSize.m_MaxR))
		{
			if (m_pCollision->CheckSecondCollisionMonsterBullet(m_pMonsterManager->GetPos(0),
																m_pAIBulletManager->GetBulletOldPos(i),
																m_pAIBulletManager->GetBulletPos(i),
																m_MonsterSize,
																m_BulletSize,
																m_pMonsterManager->GetAngle(0),
																m_pAIBulletManager->GetBulletAngle(i)))
			{
				m_pAIBulletManager->SetHit(i, true);
			}
		}
	}
}