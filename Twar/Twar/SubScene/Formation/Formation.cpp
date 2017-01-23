/**
* @file Formation.cpp
* @brief Formationクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include "Formation.h"

namespace sub_scene
{

Formation::Formation(GameDataManager* pGameDataManager)
	: SubScene(pGameDataManager)
{
}


Formation::~Formation()
{
}

SUBSCENE_ID Formation::Control()
{
	return SUBSCENE_ID::FORMATION;
}

void Formation::Draw()
{

}

}
