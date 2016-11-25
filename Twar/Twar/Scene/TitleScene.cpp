/**
* @file TitleScene.cpp
* @brief TitleSceneクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "TitleScene.h"
#include "../GameData/SaveDataManager.h"

TitleScene::TitleScene(SaveDataManager* pSaveDataManager)
	: m_pSaveDataManager(pSaveDataManager)
	, m_TitleSceneState(NONE)
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
