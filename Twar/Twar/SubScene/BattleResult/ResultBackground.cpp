/**
* @file		ResultBackground.cpp
* @brief	ResultBackgroundクラス実装
* @auhtor	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "ResultBackground.h"
#include "GameLib/GameLib.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//--------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

const BYTE		FedeInSpeed = 0x05;		// フェードインのスピード
const BYTE		AlphaMax	= 0xFF;		// アルファ値の最大値

}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

ResultBackground::ResultBackground(int texID, int vtxID)
	: m_Pos({0.0f, 0.0f})
	, m_TexID(texID)
	, m_VtxID(vtxID)
	, m_Alpha(0x00)
	, m_IsFedeInEnd(false)
{
	float backgroundWidth	= static_cast<float>(GameLib::Instance().GetWindowWidth());
	float backgroundHeight	= static_cast<float>(GameLib::Instance().GetWindowHeight());
	GameLib::Instance().CreateVtx(m_VtxID, backgroundWidth, backgroundHeight);
}


ResultBackground::~ResultBackground()
{
	// リソースはBattleResultで解放
}

bool ResultBackground::Control()
{
	if(m_Alpha == AlphaMax)
	{
		m_IsFedeInEnd = true;
	}

	m_Alpha += FedeInSpeed;

	return m_IsFedeInEnd;
}

void ResultBackground::Draw()
{
	DWORD color = D3DCOLOR_ARGB(m_Alpha, 0xFF, 0xFF, 0xFF);
	GameLib::Instance().SetVtxColor(m_VtxID, color);
	GameLib::Instance().DrawXY(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
}

void ResultBackground::EndFedeIn()
{
	m_Alpha = AlphaMax;
	m_Alpha += FedeInSpeed;		// 背景を少し暗くするため調整
	m_IsFedeInEnd = true;
}

