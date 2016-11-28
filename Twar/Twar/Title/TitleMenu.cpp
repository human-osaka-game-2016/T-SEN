/**
* @file		TitleMenu.cpp
* @brief	TitleMenuクラス実装
* @author	haga
* @todo		とりあえず実装。ここは再設計を行う
*/

#include "GameLib/GameLib.h"
#include "TitleMenu.h"
#include "../Button/MenuButton.h"

namespace{

const float			buttonWidth = 300.f;						//!< ボタンの横幅
const float			buttonHeight = 200.f;						//!< ボタンの縦幅
const D3DXVECTOR2	startButtonPos = {800.f,200.f};				//!< スタートボタンの座標
const D3DXVECTOR2	dataLoadButtonPos = { 800.f, 400.f };		//!< データロードボタンの座標

}

TitleMenu::TitleMenu(bool hasSaveData)
	: m_MenuSelectState(TitleScene::STATE::NONE)
	, m_HasSaveData(hasSaveData)
	, m_pStartButton(nullptr)
	, m_pDataLoadButton(nullptr)
{
	m_pStartButton = new MenuButton(TitleScene::BUTTON_TEX, TitleScene::START_BTN_VTX, buttonWidth, buttonHeight);

	if(m_HasSaveData)		// セーブデータがあればボタンを作成する
	{
		m_pDataLoadButton = new MenuButton(TitleScene::BUTTON_TEX, TitleScene::CONTINUE_BTN_VTX, buttonWidth, buttonHeight);
	}
}

TitleMenu::~TitleMenu()
{

}

TitleScene::STATE TitleMenu::Control()
{
	// マウスが選んでいるボタンを取得する
	m_MenuSelectState = SelectButton();

	// 上記で取得した状態を元に動作を行う
	switch(m_MenuSelectState)
	{
	case TitleScene::STATE::NONE:
		m_pStartButton->Reinstate();

		if(m_HasSaveData)
		{
			m_pDataLoadButton->Reinstate();
		}
		break;

	case TitleScene::STATE::DATA_LOAD:
		m_pDataLoadButton->Enlarge(10.f,10.f);
		break;

	case TitleScene::STATE::GAME_START:
		m_pStartButton->Enlarge(10.f, 10.f);
		break;
	}

	if(GameLib::Instance().ChecKMouseL() == ON)		
	{
		return m_MenuSelectState;
	}
	
	return TitleScene::STATE::NONE;
}

void TitleMenu::Draw()
{
	m_pStartButton->Draw(startButtonPos.x, startButtonPos.y);

	if(m_HasSaveData)
	{
		m_pDataLoadButton->Draw(dataLoadButtonPos.x, dataLoadButtonPos.y);
	}
}

TitleScene::STATE SelectButton()
{
	D3DXVECTOR2 mousePos;	// マウスの座標
	GameLib::Instance().GetMousePos(&mousePos.x,&mousePos.y);

	if(mousePos.x > startButtonPos.x && mousePos.x < ( startButtonPos.x + buttonWidth )
		&& mousePos.y > startButtonPos.y && mousePos.y < ( startButtonPos.y + buttonHeight ))
	{
		// スタートボタンを選んでいる場合
		return TitleScene::STATE::GAME_START;
	}
	else if(mousePos.x > dataLoadButtonPos.x && mousePos.x < ( dataLoadButtonPos.x + buttonWidth )
		&& mousePos.y > dataLoadButtonPos.y && mousePos.y < ( dataLoadButtonPos.y + buttonHeight ))
	{
		// データロードボタンを選んでいる場合
		return TitleScene::STATE::DATA_LOAD;
	}

	return TitleScene::STATE::NONE;
}