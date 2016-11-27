/**
* @file		MenuButton.cpp
* @brief	MenuButtonクラス実装
* @author	haga
* @todo		2016/11/24ファイル作成のみ。実装は後で行う
*/

#include "GameLib/GameLib.h"
#include "MenuButton.h"

MenuButton::MenuButton()
{
}

MenuButton::~MenuButton()
{
}

void MenuButton::SetButtonData(int texID, int vtxID, float width, float height)
{
	m_TexID = texID;
	m_VtxID = vtxID;
	m_Width = width;
	m_Height = height;
}

void MenuButton::Enlarge(float width, float height)
{
	float BtnWidth = m_Width + width;
	float BtnHeight = m_Height + height;
	GameLib::Instance().SetVtxSize(m_VtxID, BtnWidth, BtnHeight);
}

void MenuButton::Reinstate()
{
	GameLib::Instance().SetVtxSize(m_VtxID, m_Width, m_Height);
}

void MenuButton::Draw()
{
	GameLib::Instance().DrawXYCenterPos(m_TexID, m_VtxID, 0.0f, 0.0f);
}

