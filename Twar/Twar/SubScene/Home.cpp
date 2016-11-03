/**
* @file Home.cpp
* @brief Homeクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/SaveDataManager.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "Home.h"

namespace sub_scene
{

Home::Home(SaveDataManager* pSaveDataManager, GameDataManager* pGameDataManager, GameTimer* pGameTimer) 
{
	m_pSaveDataManager = pSaveDataManager;
	m_pGameDataManager = pGameDataManager;
	m_pGameTimer = pGameTimer;
}

Home::~Home()
{
}

SUBSCENE_ID Home::Control()
{
	return SUBSCENE_ID::HOME;
}

void Home::Draw()
{
}

}