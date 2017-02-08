//==================================================================================================================================//
//!< @file		ShipInfoWindow.cpp
//!< @brief		ShipInfoWindowクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "string"
#include "GameLib/GameLib.h"
#include "Font/Font.h"
#include "ShipInfoWindow.h"
#include "../SubScene/Home/HomeMenu.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const	DWORD				WindowColor = 0xccffffff;		// ウィンドウの色の設定値(アルファ値込み)
const	int					TextScaleHeight = 40;			// テキストの縦幅
const	int					TextScaleWidth = 20;			// テキストの横幅

// 軍艦情報テキストの位置座標 
const	D3DXVECTOR2			ShipTextPos[] = {
	{1175.f, 220.f},
	{1245.f, 293.f},
	{1245.f, 365.f},
	{1245.f, 438.f}
};
						
}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

ShipInfoWindow::ShipInfoWindow(const D3DXVECTOR2& rPos, int texID, int winVtxID, int textVtxID, GameDataManager* pDatamanager, HomeMenu* pHomeMenu)
	: GameWindow(rPos, texID, winVtxID)
	, m_TextVtxID(textVtxID)
	, m_pDatamanager(pDatamanager)
	, m_pHomeMenu(pHomeMenu)
	, m_pFont(nullptr)
	, m_CurrentID(GameDataManager::SHIP_ID_MAX)
{
	// ウィンドウのアルファ値を設定する
	GameLib::Instance().SetVtxColor(m_VtxID, WindowColor);

	// Fontクラス作成
	m_pFont = new Font(GameLib::Instance().GetDevice(), TextScaleHeight, TextScaleWidth);
}

ShipInfoWindow::~ShipInfoWindow()
{
	delete m_pFont;
	// リソースはシーンにて解放
}

void ShipInfoWindow::Control()
{
	GameDataManager::SHIP_ID	nextID = m_pHomeMenu->GetSelectShipID();
	if(m_CurrentID != nextID)
	{
		m_CurrentID = nextID;
		/**@todo ここでGameDataManagerからデータを受け取る予定*/
	}
	else
	{
		// テスト用空処理
	}
}

void ShipInfoWindow::Draw()
{
	if(m_CurrentID == GameDataManager::SHIP_ID_MAX)
	{ // 選択していなかったら描画しない
		return;
	}
	else
	{
		// 下の描画処理にすすむ。 テスト用空処理
	}

	GameLib::Instance().DrawXY(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
	GameLib::Instance().DrawXY(m_TexID, m_TextVtxID, m_Pos.x, m_Pos.y);

	/**@todo ここはGameDataManagerができたら調整する*/
	// 下記のswitchはテスト用
	int testNum = 1;	
	std::string text[TEXT_MAX];
	switch(m_CurrentID)
	{
	case GameDataManager::CRUISER:
		text[NAME] = "天龍";
		break;

	case GameDataManager::DESTROYER:
		text[NAME] = "峯風";
		break;

	case GameDataManager::BATTLESHIP:
		text[NAME] = "金剛";
		break;

	default:
		// do nothing
		break;
	}
	
	text[DURABILITY]	= to_string(testNum);
	text[AGGRESSIVITY]  = to_string(testNum);
	text[SPEED]			= to_string(testNum);

	for(char i = 0; i < TEXT_MAX; ++i)
	{
		m_pFont->Draw(text[i].c_str(), ShipTextPos[i], DT_LEFT, D3DCOLOR_XRGB(100, 100, 100));
	}
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
