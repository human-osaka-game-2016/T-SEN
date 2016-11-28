/**
* @file		MenuButton.cpp
* @brief	MenuButtonクラス実装
* @author	haga
* @todo		2016/11/28実装するが、バーテックスクラスを改良して再度見直す
*/

#include "GameLib/GameLib.h"
#include "MenuButton.h"

MenuButton::MenuButton(int texID, int vtxID, float width, float height, D3DXVECTOR2 pos)
	: m_TexID(texID)
	, m_VtxID(vtxID)
	, m_Width(width)
	, m_Height(height)
	, m_HasCollided(false)
	, m_Pos(pos)
{
}

MenuButton::~MenuButton()
{
}

// コントロール関数
bool MenuButton::Control()
{
	CheckCollisionCursor();

	if(m_HasCollided)
	{
		Enlarge();
	}
	else
	{
		Reinstate();
	}

	return  m_HasCollided;
}

// 描画関数
void MenuButton::Draw()
{
	GameLib::Instance().DrawXYCenterPos(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
}


// 大きさを変える
void MenuButton::Enlarge()
{
	float correctionValue = 10.f;		// 補正値
	GameLib::Instance().SetVtxSize(m_VtxID, (m_Width + correctionValue), (m_Height + correctionValue));
}

// 元に戻す
void MenuButton::Reinstate()
{
	GameLib::Instance().SetVtxSize(m_VtxID, m_Width, m_Height);
}

// マウスカーソルとの当たり判定をみている
void MenuButton::CheckCollisionCursor()
{
	D3DXVECTOR2 mousePos;
	GameLib::Instance().GetMousePos(&mousePos.x,&mousePos.y);

	/** @todo	ここの処理はバーテックスクラスを見直してサイズを取得する関数を作成し変更する*/
	float correctionValue = 0.0f;		// 補正値
	if(m_HasCollided)
	{
		correctionValue = 10.f;
	}

	if(mousePos.x > m_Pos.x && mousePos.x < (m_Width + correctionValue)
		&& mousePos.y > m_Pos.y && mousePos.y < (m_Height + correctionValue))
	{
		m_HasCollided = true;
	}
	else
	{
		m_HasCollided = false;
	}
}


