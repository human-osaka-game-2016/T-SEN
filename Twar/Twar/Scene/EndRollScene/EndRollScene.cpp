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

const	float		ScrollSpeed				= 8.f;						// テキストスクロールスピード
const	float		EndRollWidth			= 16384.f;					// エンドロールの横幅
const	float		TextWidth				= 1080.f;					// テキストの横幅
const	float		TextHeight				= 160.f;					// テキストの縦幅
const	float		WidthReducedSpeed		= 12.f;						// 横幅の縮小スピード						
const	float		HeightReducedSpeed		= 2.f;						// 縦幅の縮小スピード
const	int			StartTime				= 60;						// エンドロール開始時間
const	int			DispTime				= 180;						// 表示時間

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

EndRollScene::EndRollScene()
	: m_BackgroundPos({0.0f, 0.0f})
	, m_TextPos({800.0f, 450.0f})
	, m_EndRollPos({ -EndRollWidth, 0.0f })
	, m_ResultTextWidth(TextWidth)
	, m_ResultTextHeight(TextHeight)
	, m_StartTimeCount(0)
	, m_DispTimeCount(0)
	, m_IsFedeOutEnd(false)
{
	// Texture読み込み
	if(BattleDataManager::Instance().GetBattleResult())
	{
		m_rGameLib.LoadTex(RESULT_BG_TEX, "../Resouce/EndRoll/victoryNonText.png");
		m_rGameLib.LoadTex(RESULT_TEXT_TEX, "../Resouce/EndRoll/victoryResultText.png");
	}
	else
	{
		m_rGameLib.LoadTex(RESULT_BG_TEX, "../Resouce/EndRoll/loseNonText.png");
		m_rGameLib.LoadTex(RESULT_TEXT_TEX, "../Resouce/EndRoll/loseResultText.png");
	}

	m_rGameLib.LoadTex(END_ROLL_TEX, "../Resouce/EndRoll/staffScroll-0.png");

	float width = 1600.f;
	float height = 900.f;
	// Vertex読み込み
	m_rGameLib.CreateVtx(RESULT_BG_VTX, width, height);
	m_rGameLib.CreateVtx(END_ROLL_VTX, EndRollWidth, height);
	m_rGameLib.CreateVtx(RESULT_TEXT_VTX, m_ResultTextWidth, m_ResultTextHeight);
}

EndRollScene::~EndRollScene()
{
	m_rGameLib.ReleaseAllTex();
	m_rGameLib.ReleaseAllVertex();
}

// コントロール関数
SCENE_ID EndRollScene::Control()
{
	if(m_IsFedeOutEnd)
	{
		// 開始時間
		if(m_StartTimeCount <= StartTime)
		{
			++m_StartTimeCount;
		}
		else
		{
			if(m_EndRollPos.x == 0.0f)
			{
				if(m_DispTimeCount == DispTime)
				{
					return TITLE_SCENE;
				}
				++m_DispTimeCount;
			}
			else
			{
				m_EndRollPos.x += ScrollSpeed;
			}
		}
	}
	else
	{
		if(m_ResultTextHeight <= 0.0f && m_ResultTextWidth <= 0.0f)
		{
			m_IsFedeOutEnd = true;
		}
		else
		{
			m_ResultTextWidth -= WidthReducedSpeed;
			m_ResultTextHeight -= HeightReducedSpeed;
		}
	}

	return ENDROLL_SCENE;
}

// 描画関数
void EndRollScene::Draw()
{
	m_rGameLib.DrawXY(RESULT_BG_TEX, RESULT_BG_VTX, m_BackgroundPos.x, m_BackgroundPos.y);

	if(m_IsFedeOutEnd)
	{
		m_rGameLib.DrawXY(END_ROLL_TEX, END_ROLL_VTX, m_EndRollPos.x, m_EndRollPos.y);
	}
	else
	{
		m_rGameLib.SetVtxSize(RESULT_TEXT_VTX, m_ResultTextWidth, m_ResultTextHeight);
		m_rGameLib.DrawXYCenterPos(RESULT_TEXT_TEX, RESULT_TEXT_VTX, m_TextPos.x, m_TextPos.y);
	}
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
