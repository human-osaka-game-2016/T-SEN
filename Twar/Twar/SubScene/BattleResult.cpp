/**
* @file BattleResult.cpp
* @brief BattlerResultクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "../GameData/SaveDataManager.h"
#include "../Battle/BattleStateManager.h"
#include "BattleResult.h"

namespace sub_scene
{

BattleResult::BattleResult(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	:SubScene(pGameDataManager, pGameTimer, pSaveDataManager)
{
	m_rGameLib.LoadTex(VICTORY, "../Resouce/resultVictory.png");
	m_rGameLib.LoadTex(LOSE, "../Resouce/resultLose.png");
	m_rGameLib.CreateVtx(RESULT_DISP, 1600.f, 900.f);
}


BattleResult::~BattleResult()
{
	m_rGameLib.ReleaseAllVertex();
	m_rGameLib.ReleaseAllTex();
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
	if(BattleStateManager::Instance().CheckResult())
	{
		m_rGameLib.DrawXY(VICTORY, RESULT_DISP, 0.0f, 0.0f);
	}
	else
	{
		m_rGameLib.DrawXY(LOSE, RESULT_DISP, 0.0f, 0.0f);
	}
}

}
