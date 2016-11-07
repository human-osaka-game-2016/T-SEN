/**
* @file Shipyard.cpp
* @brief Shipyardクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "Shipyard.h"

namespace sub_scene
{

Shipyard::Shipyard(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
{
	m_pGameDataManager = pGameDataManager;
	m_pGameTimer = pGameTimer;
}


Shipyard::~Shipyard()
{
}

SUBSCENE_ID Shipyard::Control()
{
	return SUBSCENE_ID::SHIPYARD;
}

void Shipyard::Draw()
{

}

}