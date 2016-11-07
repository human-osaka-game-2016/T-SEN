/**
* @file Battle.cpp
* @brief Battleクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "Battle.h"

namespace sub_scene
{

Battle::Battle(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
{
	m_pGameDataManager = pGameDataManager;
	m_pGameTimer = pGameTimer;
}


Battle::~Battle()
{
}


SUBSCENE_ID Battle::Control()
{
	return SUBSCENE_ID::BATTLE;
}

void sub_scene::Battle::Draw()
{

}

}