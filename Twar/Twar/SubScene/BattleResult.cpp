/**
* @file BattleResult.cpp
* @brief BattlerResultクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/SaveDataManager.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "BattleResult.h"

namespace sub_scene
{

BattleResult::BattleResult(SaveDataManager* pSaveDataManager, GameDataManager* pGameDataManager, GameTimer* pGameTimer) 
{
	m_pSaveDataManager = pSaveDataManager;
	m_pGameDataManager = pGameDataManager;
	m_pGameTimer = pGameTimer;
}


BattleResult::~BattleResult()
{
}

SUBSCENE_ID BattleResult::Control()
{
	return SUBSCENE_ID::BATTLE_RESULT;
}

void BattleResult::Draw()
{

}

}