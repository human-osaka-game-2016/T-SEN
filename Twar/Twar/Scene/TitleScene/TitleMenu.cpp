/**
* @file		TitleMenu.cpp
* @brief	TitleMenuクラス実装
* @author	haga
* @todo		とりあえず実装。ここは再設計を行う
*/

#include "GameLib/GameLib.h"
#include "TitleMenu.h"
#include "../../Button/MenuButton.h"
#include "../../Button/BasicButton.h"
#include "../../Button/ButtonFunction/ButtonFunctionList.h"

/**@todo 現在数値は仮置きのもの。ここでボタンのバーテックス情報を作成しているのはなんとか直したい*/
TitleMenu::TitleMenu(bool hasSaveData)
	: m_MenuSelectState(TitleScene::STATE::NONE)
{
	float			buttonWidth = 512.f;						//!< ボタンの横幅
	float			buttonHeight = 128.f;						//!< ボタンの縦幅

	D3DXVECTOR2		startButtonPos = { 800.f, 700.f };			//!< スタートボタンの座標
	GameLib::Instance().CreateVtx(TitleScene::START_BTN_VTX, buttonWidth, buttonHeight);
	m_pButton.emplace_back(new ScaleFunction(new BasicButton(startButtonPos, TitleScene::BUTTON_TEX, TitleScene::START_BTN_VTX, buttonWidth, buttonHeight)));

	if(hasSaveData)		//　セーブデータがあればボタンを作成
	{
		//D3DXVECTOR2	dataLoadButtonPos = { 800.f, 770.f };		//!< データロードボタンの座標
		//GameLib::Instance().CreateVtx(TitleScene::START_BTN_VTX, buttonWidth, buttonHeight);
		//m_pButton.emplace_back(new ScaleFunction(new BasicButton(startButtonPos, TitleScene::BUTTON_TEX, TitleScene::CONTINUE_BTN_VTX, buttonWidth, buttonHeight)));
	}
}

TitleMenu::~TitleMenu()
{
	for(auto button : m_pButton)
	{
		delete button;
	}
	//　テクスチャーなどのリソース解放はTitleSceneのデストラクタで行う
}

// コントロール関数
TitleScene::STATE TitleMenu::Control()
{
	/** @todo	ボタンの種類の判別の為にバーテックスIDで判別しているが、ここは変更したい*/

	//　現在のボタンのバーテックスIDを格納する変数
	//　絶対入らない値で初期化している
	int currentButtonID = INT_MAX;

	for(auto button : m_pButton)
	{
		if(button->Control())
		{
			currentButtonID = button->GetVtxID();
			break;
		}
	}

	switch(currentButtonID)
	{
	case TitleScene::START_BTN_VTX:
		m_MenuSelectState = TitleScene::STATE::GAME_START;
		break;

	case TitleScene::CONTINUE_BTN_VTX:
		m_MenuSelectState = TitleScene::STATE::DATA_LOAD;
		break;

	default:
		m_MenuSelectState = TitleScene::STATE::NONE;
		break;
	}

	if(GameLib::Instance().ChecKMouseL() == ON)		
	{	// 左クリックしたら現在選んでいる状態を返す
		return m_MenuSelectState;
	}
	
	return TitleScene::STATE::NONE;
}

void TitleMenu::Draw()
{
	for(auto button : m_pButton)
	{
		button->Draw();
	}
}

