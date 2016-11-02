/**
* @file   TitleScene.cpp
* @brief  タイトルシーンのcpp
* @author haga
*/
#include "GameLib/GameLib.h"
#include "TitleScene.h"
#include "../GameData/SaveDataManager.h"

TitleScene::TitleScene(SaveDataManager* pSaveDataManager):
m_pSaveDataManager(pSaveDataManager)
{
}

TitleScene::~TitleScene()
{
}

// コントロール関数
SCENE_ID TitleScene::Control()
{
	return TITLE_SCENE;
}

// 描画関数
void TitleScene::Draw()
{
}