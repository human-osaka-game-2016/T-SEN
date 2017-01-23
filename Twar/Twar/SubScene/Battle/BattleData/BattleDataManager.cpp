/**
* @file		BattleDataManager.cpp
* @brief	BattleDataManagerクラス実装
* @author	haga
* @todo		2016/12/08にファイルだけ作成。実装はあとで行う
*/
#include "BattleDataManager.h"


BattleDataManager::BattleDataManager()
{
}


BattleDataManager::~BattleDataManager()
{
}

void BattleDataManager::SetPlayerHp(int hp)
{
	m_PlayerHp = hp;
}

void BattleDataManager::SetPlayerSpeed(float speed)
{
	m_PlayerSpeed = speed;
}