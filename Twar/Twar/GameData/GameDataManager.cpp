/**
* @file GameDataManager.cpp
* @brief GameDataManagerクラス実装
* @author haga
* @note 2016/11/03ファイル作成したが、実装はまだ行っていない
*/
#include "GameDataManager.h"


GameDataManager::GameDataManager()
	:m_Money(0)
{
	m_ShipAggressivity.m_Aggressivity[GameDataManager::ShipAggressivity::LV1] = 0;
	m_ShipDurability.m_Durability[GameDataManager::ShipDurability::LV1] = 0;
	m_ShipSpeed.m_Speed[GameDataManager::ShipSpeed::LV1] = 0;
}


GameDataManager::~GameDataManager()
{
}

void GameDataManager::SetMoney(int money)
{
	m_Money = money;
}

int GameDataManager::GetMoney()
{
	return m_Money;
}

GameDataManager::ShipAggressivity* GameDataManager::GetShipAggressivity()
{
	return &m_ShipAggressivity;
}

GameDataManager::ShipDurability* GameDataManager::GetShipDurability()
{
	return &m_ShipDurability;
}

GameDataManager::ShipSpeed* GameDataManager::GetShipSpeed()
{
	return &m_ShipSpeed;
}

void GameDataManager::SetFightOffDays(int FightOffDays)
{
	m_FightOffDays = FightOffDays;
}

int GameDataManager::GetFightOffDays()
{
	return m_FightOffDays;
}