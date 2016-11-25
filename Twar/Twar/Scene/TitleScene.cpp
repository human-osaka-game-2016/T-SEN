/**
* @file		TitleScene.cpp
* @brief	TitleSceneクラス実装
* @author	haga
*/
#include "GameLib/GameLib.h"
#include "TitleScene.h"
#include "../GameData/SaveDataManager.h"
#include "../Title/TitleBackground.h"
#include "../Title/TitleLogo.h"
#include "../Title/TitleMenu.h"

TitleScene::TitleScene(SaveDataManager* pSaveDataManager)
	: m_pSaveDataManager(pSaveDataManager)
	, m_pTitleBackground(new TitleBackground())
	, m_pTitleLogo(new TitleLogo())
	, m_pTitleMenu(new TitleMenu())
	, m_TitleSceneState(NONE)
{
	// テクスチャーとバーテックスをここで読み込み、書き込む
}

TitleScene::~TitleScene()
{	// deleteしてnullptrで初期化している
	delete m_pTitleMenu;
	m_pTitleMenu = nullptr;

	delete m_pTitleLogo;
	m_pTitleLogo = nullptr;

	delete m_pTitleBackground;
	m_pTitleBackground = nullptr;
}

// コントロール関数
SCENE_ID TitleScene::Control()
{
	if(m_TitleSceneState == DATA_LOAD)			
	{

	}
	else
	{

	}

	if(m_TitleSceneState == GAME_START)			
	{
		// ゲームスタート状態ならゲームシーンへ移行
		return GAME_SCENE;
	}

	return TITLE_SCENE;
}

// 描画関数
void TitleScene::Draw()
{

	if(m_TitleSceneState == DATA_LOAD)
	{

	}
	else
	{

	}
}
