/**
* @file LogoScene.cpp
* @brief LogoSceneクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../TeamLogo/TeamLogo.h"
#include "LogoScene.h"


LogoScene::LogoScene()
	:m_pTeamLogo (new TeamLogo())
{
}


LogoScene::~LogoScene()
{
	delete m_pTeamLogo;
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
