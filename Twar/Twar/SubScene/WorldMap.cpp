/**
* @file WorldMap.cpp
* @brief WorldMapクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "WorldMap.h"

namespace sub_scene
{

WorldMap::WorldMap(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
	: SubScene(pGameDataManager, pGameTimer)
{
}

WorldMap::~WorldMap()
{
}

SUBSCENE_ID WorldMap::Control()
{
	return SUBSCENE_ID::WORLD_MAP;
}

void WorldMap::Draw()
{
}

}
