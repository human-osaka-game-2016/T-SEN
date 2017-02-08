//==================================================================================================================================//
//!< @file		HomeMenu.cpp
//!< @brief		HomeMenuクラス実装
//!< @author	haga
//==================================================================================================================================//

//------------------------------------------------------------------------------------------------------------//
//Includes
//------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "HomeMenu.h"
#include "../../GameData/GameDatamanager.h"
#include "../../Button/BasicButton.h"
#include "../../Button/ButtonFunction/ButtonFunctionList.h"

//------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//------------------------------------------------------------------------------------------------------------//

namespace
{

const     DWORD   BrightnessVal		= 0xff505050;		// 明度基本値
const	  DWORD   BrightnessValMax  = 0xffffffff;		// 明度最大値

}

HomeMenu::HomeMenu(GameDataManager* pDataManager)
	: m_pDataManager(pDataManager)
	, m_SelectShipID(GameDataManager::SHIP_ID::SHIP_ID_MAX)
{
	// 出撃ボタン作成
	{
		D3DXVECTOR2		battleBtnPos = { 800.f, 750.f };			//!< 出撃ボタンの座標
		m_pBattleButton = new ScaleFunction(new BasicButton(battleBtnPos, sub_scene::Home::HOME_TEX, sub_scene::Home::BATTLE_START_BTN_VTX));
	}

	// 政略ボタン作成
	{
		D3DXVECTOR2		politicsBtnPos = { 450.f, 763.f };
		m_pPoliticsButton = new ScaleFunction(new BasicButton(politicsBtnPos, sub_scene::Home::HOME_TEX, sub_scene::Home::POLITICS_BTN_VTX));
	}
	
	// 軍艦選択ボタン作成
	{
		int btnCounter = 0;			// カウンター. ボタンを作成したら加算していく

		// 軍艦選択ボタンの位置座標
		D3DXVECTOR2 shipBtnPos[] = {
			{ 150.f, 325.f },
			{ 350.f, 325.f },
			{ 550.f, 325.f },
		};

		// 天龍
		m_pShipSelectButtons.emplace_back(new ScaleFunction(new BasicButton(shipBtnPos[btnCounter], sub_scene::Home::HOME_TEX, sub_scene::Home::TENRYU_BTN_VTX), 5.f));
		++btnCounter;

		/**@todo ここでDataManagerから軍艦を所有しているかの情報を取得してボタンを作成するかを判断する予定*/
		// 峯風
		if(true/*m_pDataManager->*/)
		{
			m_pShipSelectButtons.emplace_back(new ScaleFunction(new BasicButton(shipBtnPos[btnCounter], sub_scene::Home::HOME_TEX, sub_scene::Home::MINEKAZE_BTN_VTX), 5.f));
			++btnCounter;
		}

		// 金剛
		if(true/*m_pDataManager->*/)
		{
			m_pShipSelectButtons.emplace_back(new ScaleFunction(new BasicButton(shipBtnPos[btnCounter], sub_scene::Home::HOME_TEX, sub_scene::Home::KONGOU_BTN_VTX), 5.f));
		}
	}
}

HomeMenu::~HomeMenu()
{
	for(auto& shipButton : m_pShipSelectButtons)
	{
		delete shipButton;
		shipButton = nullptr;
	}
	delete m_pPoliticsButton;
	delete m_pBattleButton;
	// リソース解放はHomeシーンにて行う
}

// コントロール関数
sub_scene::SUBSCENE_ID	HomeMenu::Control()
{
	// 軍艦の選択
	GameDataManager::SHIP_ID	cuurentShipID = SelectShip();

	// 次のシーンの選択
	sub_scene::SUBSCENE_ID	nextSubSceneID = SelectSubScene();

	// 左クリックした場合、現在選択している状態で更新する
	if(GameLib::Instance().ChecKMouseL() == ON)
	{
		m_pDataManager->SetSelectedShipID(cuurentShipID);
		m_SelectShipID = cuurentShipID;
		return nextSubSceneID;
	}

	return sub_scene::SUBSCENE_ID::HOME;
}

// 描画関数
void	HomeMenu::Draw()
{
	// 明度調整
	switch(m_SelectShipID)
	{
	case GameDataManager::CRUISER:
		GameLib::Instance().SetVtxColor(sub_scene::Home::TENRYU_BTN_VTX, BrightnessValMax);
		GameLib::Instance().SetVtxColor(sub_scene::Home::MINEKAZE_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::KONGOU_BTN_VTX, BrightnessVal);
		break;

	case GameDataManager::DESTROYER:
		GameLib::Instance().SetVtxColor(sub_scene::Home::TENRYU_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::MINEKAZE_BTN_VTX, BrightnessValMax);
		GameLib::Instance().SetVtxColor(sub_scene::Home::KONGOU_BTN_VTX, BrightnessVal);
		break;

	case GameDataManager::BATTLESHIP:
		GameLib::Instance().SetVtxColor(sub_scene::Home::TENRYU_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::MINEKAZE_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::KONGOU_BTN_VTX, BrightnessValMax);
		break;

	default:
		// do nothing
		break;
	}

	for(auto& shipButton : m_pShipSelectButtons)
	{
		shipButton->Draw();
	}

	m_pPoliticsButton->Draw();

	if(m_SelectShipID != GameDataManager::SHIP_ID_MAX)
	{
		m_pBattleButton->Draw();
	}
	else
	{
		// 空処理 テストチェック用
	}
}

//------------------------------------------------------------------------------------------------------------//
//Private functions
//------------------------------------------------------------------------------------------------------------//

GameDataManager::SHIP_ID HomeMenu::SelectShip()
{
	for(auto& shipButton : m_pShipSelectButtons)
	{
		if(shipButton->Control())
		{
			switch(shipButton->GetVtxID())
			{
			case sub_scene::Home::TENRYU_BTN_VTX:
				return GameDataManager::CRUISER;
				break;

			case sub_scene::Home::MINEKAZE_BTN_VTX:
				return GameDataManager::DESTROYER;
				break;

			case sub_scene::Home::KONGOU_BTN_VTX:
				return GameDataManager::BATTLESHIP;
				break;

			default:
				// do nothing
				break;
			}
			break;
		}
	}

	return m_SelectShipID;
}

sub_scene::SUBSCENE_ID HomeMenu::SelectSubScene()
{
	if(m_pPoliticsButton->Control())
	{
		return sub_scene::SUBSCENE_ID::POLICY;
	}

	if(m_SelectShipID != GameDataManager::SHIP_ID_MAX)
	{
		if(m_pBattleButton->Control())
		{
			return sub_scene::SUBSCENE_ID::BATTLE;
		}
	}
	else
	{
		// テスト用空処理
	}

	return sub_scene::SUBSCENE_ID::HOME;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
