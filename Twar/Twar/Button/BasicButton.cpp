//==============================================================================================================================//
//!< @file		BasicButton.cpp
//!< @brief		BasicButtonクラス実装
//!< @author	haga
//==============================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "BasicButton.h"
#include "GameLib/GameLib.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

BasicButton::BasicButton(const D3DXVECTOR2& rPos, int texID, int vtxID, float width, float height)
	: m_Pos(rPos)
	, m_TexID(texID)
	, m_VtxID(vtxID)
	, m_Width(width)
	, m_Height(height)
{
	// VertexなどはvtxIDを渡してくれるクラスで作成する
}

BasicButton::~BasicButton()
{
	// リソース解放はシーンで一括解放を行う
}

bool BasicButton::Control()
{
	// ここでマウスカーソルにあたっているかを確認する
	return CheckCollisionMouseCursor();
}

void BasicButton::Draw()
{
	GameLib::Instance().DrawXYCenterPos(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
}

//--------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------//

bool BasicButton::CheckCollisionMouseCursor()
{
	// マウス座標を取得
	D3DXVECTOR2 mousePos;
	GameLib::Instance().GetMousePos(&mousePos.x, &mousePos.y);
	
	// ボタンの現在の幅を取得
	float buttonWidth  = GameLib::Instance().GetVtxWidth(m_VtxID);
	float buttonHeight = GameLib::Instance().GetVtxHeight(m_VtxID);

	// 割る2をしているのは位置座標がTextureの真ん中にある為
	if (mousePos.x > m_Pos.x - (buttonWidth / 2) && mousePos.x < (m_Pos.x + buttonWidth / 2)
		&& mousePos.y > m_Pos.y - (buttonHeight / 2) && mousePos.y < (m_Pos.y + buttonHeight / 2))
	{
		// マウスカーソルが範囲内にあたっている場合
		return true;
	}
	else
	{	// マウスカーソルが範囲内にあたっていない場合
		// return false;	テスト用の空処理
	}

	return false;
}

//============================================================================================================================//
//END OF FILE
//============================================================================================================================//
