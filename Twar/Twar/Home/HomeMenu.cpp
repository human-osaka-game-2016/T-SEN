/**
* @file		HomeMenu.cpp
* @brief	HomeMenuクラス実装
* @author	haga
*/

//------------------------------------------------------------------------------------------------------------//
//Includes
//------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "HomeMenu.h"
#include "../Button/MenuButton.h"

//------------------------------------------------------------------------------------------------------------//
//Public functions
//------------------------------------------------------------------------------------------------------------//

// 数字は仮置き
HomeMenu::HomeMenu()
	: m_MenuSelectState(sub_scene::Home::NOMAL)
{
	float			buttonWidth = 512.f;						//!< ボタンの横幅
	float			buttonHeight = 128.f;						//!< ボタンの縦幅

	D3DXVECTOR2		battleStartBtnPos = { 800.f, 780.f };			//!< 出撃ボタンの座標
	GameLib::Instance().CreateVtx(sub_scene::Home::BATTLE_START_BTN_VTX, buttonWidth, buttonHeight);
	GameLib::Instance().SetVtxUV(sub_scene::Home::BATTLE_START_BTN_VTX, 0.0f, 1.0f, 0.0f, 1.0f);
	m_MenuButton.emplace_back(sub_scene::Home::MENU_BTN_TEX, sub_scene::Home::BATTLE_START_BTN_VTX, buttonWidth, buttonHeight, battleStartBtnPos);
}


HomeMenu::~HomeMenu()
{
	// リソース解放はHomeシーンにて行う
}

// コントロール関数
sub_scene::Home::STATE	HomeMenu::Control()
{
	//　現在のボタンのバーテックスIDを格納する変数
	//　絶対入らない値で初期化している
	int currentButtonID = INT_MAX;
	m_MenuSelectState = sub_scene::Home::NOMAL;

	for(auto button : m_MenuButton)
	{
		if(button.Control())
		{
			currentButtonID = button.GetVtxID();
			break;
		}
	}

	switch(currentButtonID)
	{
	case sub_scene::Home::BATTLE_START_BTN_VTX:				// 出撃ボタン
		m_MenuSelectState = sub_scene::Home::BATTLE_START;
		break;
	}

	if(GameLib::Instance().ChecKMouseL() == ON)
	{
		// マウスを左クリックしたら現在選んでいる状態を返す
		return m_MenuSelectState;
	}

	return sub_scene::Home::NOMAL;
}

// 描画関数
void	HomeMenu::Draw()
{
	for(auto button : m_MenuButton)
	{
		button.Draw();
	}
}
