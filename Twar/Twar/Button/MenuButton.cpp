/**
* @file		MenuButton.cpp
* @brief	MenuButtonクラス実装
* @author	haga
* @todo		2016/11/24ファイル作成のみ。実装は後で行う
*/

#include "GameLib/GameLib.h"
#include "MenuButton.h"

MenuButton::MenuButton(int texID, int vtxID, float width, float height)
	: m_TexID(texID)
	, m_VtxID(vtxID)
	, m_Width(width)
	, m_Height(height)
{
	GameLib::Instance().CreateVtx(m_VtxID,width,height);
}

MenuButton::~MenuButton()
{
}

// 大きさを変える
void MenuButton::Enlarge(float width, float height)
{
	float BtnWidth = m_Width + width;
	float BtnHeight = m_Height + height;
	GameLib::Instance().SetVtxSize(m_VtxID, BtnWidth, BtnHeight);
}

// 元に戻す
void MenuButton::Reinstate()
{
	GameLib::Instance().SetVtxSize(m_VtxID, m_Width, m_Height);
}

void MenuButton::Draw(float posX, float posY)
{
	GameLib::Instance().DrawXYCenterPos(m_TexID, m_VtxID, posX, posY);
}

