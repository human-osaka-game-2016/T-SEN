//==================================================================================================================================//
//!< @file		EndRollScene.cpp
//!< @brief		EndRollSceneクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "../../SubScene/Battle/BattleData/BattleDataManager.h"
#include "EndRollScene.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const	float		TextScrollSpeed = 8.f;			// テキストスクロールスピード
const	float		TextWidth = 16384.f;			// テキストの横幅
const	int			DispTime = 180;					// 表示時間

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

EndRollScene::EndRollScene()
	: m_BackgroundPos({0.0f, 0.0f})
	, m_TextPos({ -TextWidth, 0.0f })
	, m_DispTimeCount(0)
{
	// Texture読み込み
	if(BattleDataManager::Instance().GetBattleResult())
	{
		m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/EndRoll/victoryNonText.png");
	}
	else
	{
		m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/EndRoll/loseNonText.png");
	}

	m_rGameLib.LoadTex(TEXT_TEX, "../Resouce/EndRoll/staffScroll-0.png");

	float width = 1600.f;
	float height = 900.f;
	// Vertex読み込み
	m_rGameLib.CreateVtx(RESULT_VTX, width, height);
	m_rGameLib.CreateVtx(TEXT_VTX, TextWidth, height);
}

EndRollScene::~EndRollScene()
{
	m_rGameLib.ReleaseAllTex();
	m_rGameLib.ReleaseAllVertex();
}

// コントロール関数
SCENE_ID EndRollScene::Control()
{
	if(m_TextPos.x == 0.0f)
	{
		if(m_DispTimeCount == DispTime)
		{
			return TITLE_SCENE;
		}
		++m_DispTimeCount;
	}
	else
	{
		m_TextPos.x += TextScrollSpeed;
	}

	return ENDROLL_SCENE;
}

// 描画関数
void EndRollScene::Draw()
{
	m_rGameLib.DrawXY(RESULT_TEX, RESULT_VTX, m_BackgroundPos.x, m_BackgroundPos.y);
	m_rGameLib.DrawXY(TEXT_TEX, TEXT_VTX, m_TextPos.x, m_TextPos.y);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
