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
	m_rGameLib.LoadTex(1,"../Resouce//resultVictory.png");
	m_rGameLib.CreateVtx(1,1600.f,900.f);
}


BattleResult::~BattleResult()
{
}

SUBSCENE_ID BattleResult::Control()
{
	if(m_rGameLib.CheckKey(DIK_SPACE, SPACE) == ON)
	{
		return SUBSCENE_ID::HOME;
	}
	return SUBSCENE_ID::BATTLE_RESULT;
}

void BattleResult::Draw()
{
	m_rGameLib.DrawXY(1,1,0.0f,0.0f);
}

}
