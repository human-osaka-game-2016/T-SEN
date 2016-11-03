/**
* @file Situation.cpp
* @brief Situationクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "WorldSituation.h"

namespace sub_scene
{

WorldSituation::WorldSituation(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
{
	m_pGameDataManager = pGameDataManager;
	m_pGameTimer = pGameTimer;
}


WorldSituation::~WorldSituation()
{
}

SUBSCENE_ID WorldSituation::Control()
{
	return SUBSCENE_ID::WORLD_SITUATION;
}

void WorldSituation::Draw()
{

}

}