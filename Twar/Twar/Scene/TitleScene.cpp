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
	GameLib::GetInstance().LoadTexEx(1, "../Resouce//title.jpg", 255, 0, 0, 0, false);
	GameLib::GetInstance().CreateVtx(1,1600,900);
}

TitleScene::~TitleScene()
{
	GameLib::GetInstance().ReleaseTex(true);
}

// コントロール関数
SCENE_ID TitleScene::Control()
{
	if (GameLib::GetInstance().ChecKMouseL() == ON)
	{
		return GAME_SCENE;
	}
	return TITLE_SCENE;
}

// 描画関数
void TitleScene::Draw()
{
	GameLib::GetInstance().DrawXY(1,1,false,0,0);
}