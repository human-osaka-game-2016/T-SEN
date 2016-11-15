/**
* @file BattleResult.cpp
* @brief BattlerResultクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "../GameData/SaveDataManager.h"
#include "BattleResult.h"

namespace sub_scene
{

BattleResult::BattleResult(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	:SubScene(pGameDataManager, pGameTimer, pSaveDataManager)
{
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
