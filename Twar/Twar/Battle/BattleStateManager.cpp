/**
* @file		BattleStateManager.cpp
* @brief	BattleStateManagerクラス実装
* @author	haga
* @todo		2016/12/08にファイルだけ作成。実装はあとで行う
*/


#include "BattleStateManager.h"


BattleStateManager::BattleStateManager()
	: m_IsEnd(false)
	, m_IsVictory(false)
	, m_IsZoom(false)
{
}

BattleStateManager::~BattleStateManager()
{
}

void BattleStateManager::Init()
{
	m_IsEnd = false;
	m_IsVictory = false;
}

void BattleStateManager::SetMonsterHP(int monsterHp)
{
	m_MonsterHP = monsterHp;
}

void BattleStateManager::SetPlayerHP(int playerHp)
{
	m_PlayerHP = playerHp;
}

void BattleStateManager::SetShipSpeed(float shipSpeed)
{
	m_ShipSpeed = shipSpeed;
}

void BattleStateManager::SetShipID(ShipManager::SHIP_ID    chosenShipID)
{
	m_ChosenShipID = chosenShipID;
}

void BattleStateManager::SetGameResult(bool isVictory)
{
	m_IsEnd = true;
	m_IsVictory = isVictory;
}

void BattleStateManager::SetZoomFlag(bool isZoom)
{
	m_IsZoom = isZoom;
}
