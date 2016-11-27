/**
* @file		TitleMenu.cpp
* @brief	TitleMenuクラス実装
* @author	haga
* @todo		2016/11/24ファイル作成のみ。実装は後で行う
*/

#include "GameLib/GameLib.h"
#include "TitleMenu.h"
#include "../Scene/TitleScene.h"
#include "../Button/MenuButton.h"


TitleMenu::TitleMenu()
	: m_CurrentMenu(NONE)
	, m_HasSaveData(false)
{
	m_pStartBtn = new MenuButton();
	m_pDataLoadBtn = new MenuButton();
}

TitleMenu::~TitleMenu()
{
}

TITLE_STATE TitleMenu::Control()
{


	if(GameLib::Instance().ChecKMouseL() == ON)
	{
		return m_CurrentMenu;
	}

	return TITLE_STATE::NONE;
}

void TitleMenu::Draw()
{
	m_pStartBtn->Draw();

	if(m_HasSaveData)
	{
		m_pDataLoadBtn->Draw();
	}
}
