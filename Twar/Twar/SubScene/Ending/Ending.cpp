/**
* @file Ending.cpp
* @brief Endingクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "Ending.h"

namespace sub_scene
{

sub_scene::Ending::Ending(GameDataManager* pGameDataManager)
	: SubScene(pGameDataManager)
{
}


sub_scene::Ending::~Ending()
{
}

SUBSCENE_ID sub_scene::Ending::Control()
{
	return SUBSCENE_ID::ENDING;
}

void sub_scene::Ending::Draw()
{

}

}
