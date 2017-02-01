//==================================================================================================================================//
//!< @file		HomeBackground.cpp
//!< @brief		HomeBackgroundクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "HomeBackground.h"
#include "Home.h"

//------------------------------------------------------------------------------------------------------------//
//Public functions
//------------------------------------------------------------------------------------------------------------//

HomeBackground::HomeBackground(int texID, int vtxID)
	: m_Pos({0.0f, 0.0f})
	, m_TexID(texID)
	, m_VtxID(vtxID)
{
	float backgroundWidth	= static_cast<float>(GameLib::Instance().GetWindowWidth());
	float backgroundHeight  = static_cast<float>(GameLib::Instance().GetWindowHeight());
	GameLib::Instance().CreateVtx(m_VtxID, backgroundWidth, backgroundHeight);
}

HomeBackground::~HomeBackground()
{
	// リソース解放はHomeシーンにて行う
}

void HomeBackground::Draw()
{
	GameLib::Instance().DrawXY(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
