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

HomeMenu::HomeMenu(GameDataManager* pDatamanager)
	: m_pDataManager(pDatamanager)
	, m_SelectShipID(ShipManager::NONE)
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
		int btnCounter = 0;
		D3DXVECTOR2 shipBTNPos[] = {
			{ 150.f, 325.f },
			{ 350.f, 325.f },
			{ 550.f, 325.f },
		};

		// 天龍
		m_pShipSelectButtons.emplace_back(new ScaleFunction(new BasicButton(shipBTNPos[btnCounter], sub_scene::Home::HOME_TEX, sub_scene::Home::TENRYU_BTN_VTX), 5.f));
		++btnCounter;

		/**@todo */
		// 峯風
		if(true/*m_pDataManager->*/)
		{
			m_pShipSelectButtons.emplace_back(new ScaleFunction(new BasicButton(shipBTNPos[btnCounter], sub_scene::Home::HOME_TEX, sub_scene::Home::MINEKAZE_BTN_VTX), 5.f));
			++btnCounter;
		}

		// 金剛
		if(true/*m_pDataManager->*/)
		{
			m_pShipSelectButtons.emplace_back(new ScaleFunction(new BasicButton(shipBTNPos[btnCounter], sub_scene::Home::HOME_TEX, sub_scene::Home::KONGOU_BTN_VTX), 5.f));
		}
	}
}

HomeMenu::~HomeMenu()
{
	for(auto& shipBTN : m_pShipSelectButtons)
	{
		delete shipBTN;
		shipBTN = nullptr;
	}
	delete m_pPoliticsButton;
	delete m_pBattleButton;
	// リソース解放はHomeシーンにて行う
}

// コントロール関数
sub_scene::SUBSCENE_ID	HomeMenu::Control()
{
	// 軍艦の選択
	ShipManager::SHIP_ID	cuurentShipID = SelectShip();

	// 次のシーンの選択
	sub_scene::SUBSCENE_ID	nextSubSceneID = SelectSubScene();

	// 左クリックした場合、現在選んでいる状態を更新する
	if(GameLib::Instance().ChecKMouseL() == ON)
	{
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
	case ShipManager::CRUISER:
		GameLib::Instance().SetVtxColor(sub_scene::Home::TENRYU_BTN_VTX, BrightnessValMax);
		GameLib::Instance().SetVtxColor(sub_scene::Home::MINEKAZE_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::KONGOU_BTN_VTX, BrightnessVal);
		break;

	case ShipManager::DESTROYER:
		GameLib::Instance().SetVtxColor(sub_scene::Home::TENRYU_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::MINEKAZE_BTN_VTX, BrightnessValMax);
		GameLib::Instance().SetVtxColor(sub_scene::Home::KONGOU_BTN_VTX, BrightnessVal);
		break;

	case ShipManager::BATTLESHIP:
		GameLib::Instance().SetVtxColor(sub_scene::Home::TENRYU_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::MINEKAZE_BTN_VTX, BrightnessVal);
		GameLib::Instance().SetVtxColor(sub_scene::Home::KONGOU_BTN_VTX, BrightnessValMax);
		break;

	default:
		// do nothing
		break;
	}

	for(auto& shipBTN : m_pShipSelectButtons)
	{
		shipBTN->Draw();
	}

	m_pPoliticsButton->Draw();

	if(m_SelectShipID != ShipManager::NONE)
	{
		m_pBattleButton->Draw();
	}
	else
	{
		// 空処理
	}
}

//------------------------------------------------------------------------------------------------------------//
//Private functions
//------------------------------------------------------------------------------------------------------------//

ShipManager::SHIP_ID HomeMenu::SelectShip()
{
	for(auto& shipBTN : m_pShipSelectButtons)
	{
		if(shipBTN->Control())
		{
			switch(shipBTN->GetVtxID())
			{
			case sub_scene::Home::TENRYU_BTN_VTX:
				return ShipManager::CRUISER;
				break;

			case sub_scene::Home::MINEKAZE_BTN_VTX:
				return ShipManager::DESTROYER;
				break;

			case sub_scene::Home::KONGOU_BTN_VTX:
				return ShipManager::BATTLESHIP;
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
		/**@todo 2017/02/02 まだ政略Sceneがない*/
		// return sub_scene::SUBSCENE_ID::;
	}

	if(m_SelectShipID != ShipManager::NONE)
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
