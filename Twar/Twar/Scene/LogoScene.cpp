/**
* @file LogoScene.cpp
* @brief LogoSceneクラス実装
* @author haga.ichikawa
*/
#include "GameLib/GameLib.h"
#include "../TeamLogo/TeamLogo.h"
#include "LogoScene.h"


LogoScene::LogoScene()
	: m_pTeamLogo (new TeamLogo())
{

}


LogoScene::~LogoScene()
{
	delete m_pTeamLogo;
	m_rGameLib.ReleaseAllTex();
	m_rGameLib.ReleaseAllVertex();
}

// コントロール関数
SCENE_ID LogoScene::Control()
{
	if (m_pTeamLogo->Contlrol())
	{
		return TITLE_SCENE;
	}
	if (m_rGameLib.CheckKey(DIK_SPACE, SPACE) == ON)
	{
		return TITLE_SCENE;
	}
	return LOGO_SCENE;

}

// 描画関数
void LogoScene::Draw()
{
	m_pTeamLogo->Draw();
}
