﻿//==================================================================================================================================//
//!< @file		TimeLimitWindow.cpp
//!< @brief		TimeLimitWindowクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <string>
#include "TimeLimitWindow.h"
#include "../GameData/GameDataManager.h"
#include "GameLib/GameLib.h"
#include "Font/Font.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

TimeLimitWindow::TimeLimitWindow(const D3DXVECTOR2& rPos, int texID, int vtxID)
	: GameWindow(rPos, texID, vtxID)
{
	// Vertexはシーンで作成する
}

TimeLimitWindow::~TimeLimitWindow()
{
	// リソースはシーンにて解放
}

void TimeLimitWindow::Control()
{
	// 特に制御的なものはない。空処理
}

void TimeLimitWindow::Draw()
{
	GameLib::Instance().DrawXY(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
