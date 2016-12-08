/**
* @file LogoScene.cpp
* @brief LogoSceneクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "LogoScene.h"
#include "TeamLogo.h"

LogoScene::LogoScene()
{
}


LogoScene::~LogoScene()
{
}

// コントロール関数
SCENE_ID LogoScene::Control()
{
	return LOGO_SCENE;
}

// 描画関数
void LogoScene::Draw()
{
	m_pTeamLogo->Draw();
}
