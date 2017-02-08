/**
* @file GameDataManager.cpp
* @brief GameDataManagerクラス実装
* @author haga
* @note 2016/11/03ファイル作成したが、実装はまだ行っていない
*/
#include "GameDataManager.h"


GameDataManager::GameDataManager()
{
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