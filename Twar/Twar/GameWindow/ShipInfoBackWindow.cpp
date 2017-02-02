//==================================================================================================================================//
//!< @file		ShipInfoBackWindow.cpp
//!< @brief		ShipInfoBackWindowクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "ShipInfoBackWindow.h"
#include "../SubScene/Home/HomeMenu.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

ShipInfoBackWindow::ShipInfoBackWindow(const D3DXVECTOR2& rPos, int texID, int tenryuVtxID, int minekazeVtxID, int kongouVtxID, HomeMenu* pHomeMenu)
	: GameWindow(rPos, texID, tenryuVtxID)
	, m_pHomeMenu(pHomeMenu)
	, m_MinekazeVtxID(minekazeVtxID)
	, m_KongouVtxID(kongouVtxID)
	, m_CurrentID(ShipManager::NONE)
{}

ShipInfoBackWindow::~ShipInfoBackWindow()
{
	// リソースはシーンにて解放
}

void ShipInfoBackWindow::Control()
{
	ShipManager::SHIP_ID	nextID = m_pHomeMenu->GetSelectShipID();
	if(m_CurrentID != nextID)
	{
		m_CurrentID = nextID;
	}
	else
	{
		// テスト用空処理
	}
}

void ShipInfoBackWindow::Draw()
{
	if(m_CurrentID == ShipManager::NONE)
	{ // 選択していなかったら描画しない
		return;
	}
	else
	{
		// 下の描画処理にすすむ。 テスト用空処理
	}

	switch(m_CurrentID)
	{
	case ShipManager::CRUISER:
		GameLib::Instance().DrawXY(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
		break;

	case ShipManager::DESTROYER:
		GameLib::Instance().DrawXY(m_TexID, m_MinekazeVtxID, m_Pos.x, m_Pos.y);
		break;

	case ShipManager::BATTLESHIP:
		GameLib::Instance().DrawXY(m_TexID, m_KongouVtxID, m_Pos.x, m_Pos.y);
		break;

	default:
		// do nothing
		break;
	}
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
