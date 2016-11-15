/**
* @file SubScene.cpp
* @brief   SubSceneクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "SubScene.h"

namespace sub_scene
{

SubScene::SubScene(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	: m_rGameLib(GameLib::Instance())
	, m_pGameDataManager(pGameDataManager)
	, m_pGameTimer(pGameTimer)
	, m_pSaveDataManager(pSaveDataManager)
{
}


SubScene::~SubScene()
{
}

}
