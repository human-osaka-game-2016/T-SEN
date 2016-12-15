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
	, m_TitleSceneState(TitleScene::STATE::NONE)
{
	/** @todo ここでセーブデータの有無をメニュークラスにわたす。仕組みはまだ未実装nのためfalseを渡している */
	m_pTitleMenu = new TitleMenu(false);
	Init();
}

TitleScene::~TitleScene()
{
	delete m_pTitleMenu;
	m_pTitleMenu = nullptr;

	delete m_pTitleLogo;
	m_pTitleLogo = nullptr;

	delete m_pTitleBackground;
	m_pTitleBackground = nullptr;

	m_rGameLib.ReleaseAllTex();
	m_rGameLib.ReleaseAllVertex();
}

// コントロール関数
SCENE_ID TitleScene::Control()
{
	switch( m_TitleSceneState )
	{
	case TitleScene::STATE::NONE:					// 通常モード
		m_pTitleLogo->Control();
		m_TitleSceneState = m_pTitleMenu->Control();
		break;

	case TitleScene::STATE::DATA_LOAD:				// データロード画面を描画

		/**@todo	2016/11/27：まだ実装していない*/

		break;

	case TitleScene::STATE::GAME_START:			// ゲームを開始する

			return GAME_SCENE;
		break;
	}
	
	return TITLE_SCENE;
}

// 描画関数
void TitleScene::Draw()
{
	m_pTitleBackground->Draw();

	if(m_TitleSceneState == TitleScene::STATE::DATA_LOAD)
	{
		/**@todo	2016/11/27：まだ実装していない*/

	}
	else
	{
		//m_pTitleLogo->Draw();
		m_pTitleMenu->Draw();
	}
}

//------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//------------------------------------------------------------------------------------------------------------------------------------//

void TitleScene::Init()
{
	// テクスチャーを読み込む
	GameLib::Instance().LoadTexEx(BACKGROUND_TEX, "../Resouce/TitleScene/titleBackground.png", 255, 0, 0, 0, false);
	GameLib::Instance().LoadTex(BUTTON_TEX, "../Resouce/TitleScene/titleStartButton.png");
}

