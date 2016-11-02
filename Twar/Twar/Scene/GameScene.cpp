/**
* @file GameScene.cpp
* @brief ゲームシーンのcpp
* @author haga
*/
#include "GameScene.h"
#include "../GameData/SaveDataManager.h"


GameScene::GameScene(SaveDataManager* pSaveDataManager):
m_pSaveDataManager()
{
}


GameScene::~GameScene()
{
}

// コントロール関数
SCENE_ID GameScene::Control()
{
	return GAME_SCENE;
}

// 描画関数
void GameScene::Draw()
{

}