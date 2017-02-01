/**
* @file Policy.cpp
* @brief Policyクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include "../../GameData/GameTimer.h"
#include "Policy.h"

namespace sub_scene
{

Policy::Policy(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
	: SubScene(pGameDataManager, pGameTimer)
{
}


Policy::~Policy()
{
}

SUBSCENE_ID Policy::Control()
{
	return SUBSCENE_ID::POLICY;
}

void Policy::Draw()
{

}

}
