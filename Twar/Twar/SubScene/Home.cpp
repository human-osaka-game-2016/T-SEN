/**
* @file Home.cpp
* @brief Homeクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "../GameData/SaveDataManager.h"
#include "Home.h"

namespace sub_scene
{

Home::Home(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	: SubScene(pGameDataManager, pGameTimer, pSaveDataManager)
{
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
