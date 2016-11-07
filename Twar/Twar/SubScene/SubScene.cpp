/**
* @file SubScene.cpp
* @brief   SubSceneクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "SubScene.h"

namespace sub_scene
{

SubScene::SubScene()
	: m_pSaveDataManager(nullptr)
	, m_pGameDataManager(nullptr)
	, m_pGameTimer(nullptr)
{
}


SubScene::~SubScene()
{
}

}
