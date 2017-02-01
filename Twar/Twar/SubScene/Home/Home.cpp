//==================================================================================================================================//
//!< @file		Home.cpp
//!< @brief		Homeクラス実装
//!< @author	haga
//==================================================================================================================================//

//------------------------------------------------------------------------------------------------------------//
//Includes
//------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include "../../GameData/GameTimer.h"
#include "../../GameData/SaveDataManager.h"
#include "Home.h"
#include "HomeBackGround.h"
#include "HomeMenu.h"
#include "../../GameWindow/GameWindow.h"
#include "../../GameWindow/ShipInfoWindow.h"
#include "../../GameWindow/ShipInfoBackWindow.h"
#include "../../GameWindow/TimeLimitWindow.h"

//-----------------------------------------------------------------------------------------------------------//
//Namespace sub_scene
//-----------------------------------------------------------------------------------------------------------//

namespace sub_scene
{

//-----------------------------------------------------------------------------------------------------------//
//Unnamed namespace 
//-----------------------------------------------------------------------------------------------------------//

namespace
{

const	float			HomeTextureWidth	  = 2048.f;						//	Home::HOME_TEXの横幅
const	float			HomeTextureHeight	  = 2048.f;						//	Home::HOME_TEXの横幅
const	D3DXVECTOR2		ShipInfoWinPos		  = {  825.f, 150.f };			//	軍艦情報ウィンドウの位置座標
const	D3DXVECTOR2		ShipInfoBackWinPos	  = {  700.f,  50.f };			//	軍艦情報背景ウィンドウの位置座標
const	D3DXVECTOR2		TimeLimitWinPos		  = {  900.f, 625.f };			//	撃退期限ウィンドウの位置座標

}

//----------------------------------------------------------------------------------------------------------//
//Public functions
//----------------------------------------------------------------------------------------------------------//

Home::Home(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	: SubScene(pGameDataManager, pGameTimer, pSaveDataManager)
	, m_pBackground(nullptr)
	, m_pHomeMenu(nullptr)
{
	Init();
	m_pHomeMenu = new HomeMenu(pGameDataManager);
	m_pGameWindows.emplace_back(new ShipInfoBackWindow(ShipInfoBackWinPos, Home::HOME_TEX, SHIP_INFO_BG_TENRYU_VTX, SHIP_INFO_BG_MINEKAZE_VTX, SHIP_INFO_BG_KONGOU_VTX, m_pHomeMenu));
	m_pGameWindows.emplace_back(new ShipInfoWindow(ShipInfoWinPos, Home::HOME_TEX, SHIP_INFO_WIN_VTX, SHIP_INFO_TEXT_VTX, m_pGameDataManager, m_pHomeMenu));
	/**@todo ここでGameDataManagerからタイムリミットの数値を取得する*/
	//int	  timeLimit = m_pGameDataManager->GetFightOffDays();

	int	  testTimeLimit = 0; // テスト用変数

	/**Caseの数字は残日数*/
	switch(testTimeLimit)
	{
	case 3:
		m_pGameWindows.emplace_back(new TimeLimitWindow(TimeLimitWinPos, Home::HOME_TEX, TIME_LIMIT_WIN_3_VTX));
		break;

	case 2:
		m_pGameWindows.emplace_back(new TimeLimitWindow(TimeLimitWinPos, Home::HOME_TEX, TIME_LIMIT_WIN_2_VTX));
		break;

	case 1:
		m_pGameWindows.emplace_back(new TimeLimitWindow(TimeLimitWinPos, Home::HOME_TEX, TIME_LIMIT_WIN_1_VTX));
		break;

	default:
		// 3日以内じゃないならウィンドウを作成しない
		break;
	}
}

Home::~Home()
{
	m_rGameLib.ReleaseAllVertex();
	m_rGameLib.ReleaseAllTex();

	for(auto& pWindow : m_pGameWindows)
	{
		delete pWindow;
		pWindow = nullptr;
	}

	delete m_pHomeMenu;
	delete m_pBackground;
}

SUBSCENE_ID Home::Control()
{
	SUBSCENE_ID nextSubSceneID = m_pHomeMenu->Control();

	for(auto& pWindow : m_pGameWindows)
	{
		pWindow->Control();
	}

	return nextSubSceneID;
}

void Home::Draw()
{
	m_pBackground->Draw();
	m_pHomeMenu->Draw();
	for(auto& pWindow : m_pGameWindows)
	{
		pWindow->Draw();
	}
}

//-----------------------------------------------------------------------------------------------------------//
//Private functions
//-----------------------------------------------------------------------------------------------------------//

void Home::Init()
{
	m_rGameLib.LoadTexEx(Home::BACKGROUND_TEX, "../Resouce/HomeScene/background_0.png", 255, 0, 0, 0, false);
	m_rGameLib.LoadTex(Home::HOME_TEX, "../Resouce/HomeScene/tinjyuhu_0.png");

	// Home::HOME_TEXのテクスチャーにおける位置座標
	D3DXVECTOR2		texPos[VTX_MAX] =
	{
		{   0.0f,   0.0f},	// 背景 ※この座標は使用しない
		{  300.f,   0.0f},	// 出撃ボタン
		{  300.f,  200.f},	// 政略ボタン
		{  700.f,   0.0f},	// 軍艦情報ウィンドウ
		{ 1300.f,   0.0f},	// 軍艦情報のテキスト
		{	0.0f,  250.f},	// 撃退期限表示ウィンドウ(残り三日)
		{  150.f,  250.f},	// 撃退期限表示ウィンドウ(残り二日)
		{	0.0f,  325.f},	// 撃退期限表示ウィンドウ(残り一日)
		{   0.0f,   0.0f},	// 天龍選択ボタン
		{  100.f,   0.0f},	// 峯風選択ボタン
		{  200.f,   0.0f},	// 金剛選択ボタン
		{  850.f,  400.f},	// 軍艦情報背景ウィンドウ(天龍)
		{   0.0f,  400.f},	// 軍艦情報背景ウィンドウ(峯風)
		{   0.0f,  950.f},	// 軍艦情報背景ウィンドウ(金剛)
	};

	// 背景作成
	m_pBackground = new HomeBackground(Home::BACKGROUND_TEX, Home::BACKGROUND_VTX);

	// 出撃ボタンVertex作成ブロック
	{
		float width = 400.f;
		float height = 200.f;
		m_rGameLib.CreateVtx(BATTLE_START_BTN_VTX, width, height);
		m_rGameLib.SetVtxUV(BATTLE_START_BTN_VTX, texPos[BATTLE_START_BTN_VTX].x / HomeTextureWidth, (texPos[BATTLE_START_BTN_VTX].x + width) / HomeTextureWidth,
							texPos[BATTLE_START_BTN_VTX].y / HomeTextureHeight, (texPos[BATTLE_START_BTN_VTX].y + height) / HomeTextureHeight);
	}

	// 政略ボタンVertex作成ブロック
	{
		float width  = 200.f;
		float height = 125.f;
		m_rGameLib.CreateVtx(POLITICS_BTN_VTX, width, height);
		m_rGameLib.SetVtxUV(POLITICS_BTN_VTX, texPos[POLITICS_BTN_VTX].x / HomeTextureWidth, (texPos[POLITICS_BTN_VTX].x + width) / HomeTextureWidth,
							texPos[POLITICS_BTN_VTX].y / HomeTextureHeight, (texPos[POLITICS_BTN_VTX].y + height) / HomeTextureHeight);
	}

	// 軍艦情報ウィンドウVertex作成ブロック
	{
		float width = 600.f;
		float height = 400.f;
		m_rGameLib.CreateVtx(SHIP_INFO_WIN_VTX, width, height);
		m_rGameLib.SetVtxUV(SHIP_INFO_WIN_VTX, texPos[SHIP_INFO_WIN_VTX].x / HomeTextureWidth, (texPos[SHIP_INFO_WIN_VTX].x + width) / HomeTextureWidth,
							texPos[SHIP_INFO_WIN_VTX].y / HomeTextureHeight, (texPos[SHIP_INFO_WIN_VTX].y  + height)/ HomeTextureHeight);

		m_rGameLib.CreateVtx(SHIP_INFO_TEXT_VTX, width, height);
		m_rGameLib.SetVtxUV(SHIP_INFO_TEXT_VTX, texPos[SHIP_INFO_TEXT_VTX].x / HomeTextureWidth, (texPos[SHIP_INFO_TEXT_VTX].x + width) / HomeTextureWidth,
							texPos[SHIP_INFO_TEXT_VTX].y / HomeTextureHeight, (texPos[SHIP_INFO_TEXT_VTX].y + height) / HomeTextureHeight);

	}

	// 期限リミットウィンドウVertex作成ブロック
	{
		float width = 150.f;
		float height = 75.f;

		// 残り3日
		m_rGameLib.CreateVtx(TIME_LIMIT_WIN_3_VTX, width, height);
		m_rGameLib.SetVtxUV(TIME_LIMIT_WIN_3_VTX, texPos[TIME_LIMIT_WIN_3_VTX].x / HomeTextureWidth, (texPos[TIME_LIMIT_WIN_3_VTX].x + width) / HomeTextureWidth,
							texPos[TIME_LIMIT_WIN_3_VTX].y / HomeTextureHeight, (texPos[TIME_LIMIT_WIN_3_VTX].y + height) / HomeTextureHeight);

		// 残り2日
		m_rGameLib.CreateVtx(TIME_LIMIT_WIN_2_VTX, width, height);
		m_rGameLib.SetVtxUV(TIME_LIMIT_WIN_2_VTX, texPos[TIME_LIMIT_WIN_2_VTX].x / HomeTextureWidth, (texPos[TIME_LIMIT_WIN_2_VTX].x + width) / HomeTextureWidth,
							texPos[TIME_LIMIT_WIN_2_VTX].y / HomeTextureHeight, (texPos[TIME_LIMIT_WIN_2_VTX].y + height) / HomeTextureHeight);


		// 残り1日
		m_rGameLib.CreateVtx(TIME_LIMIT_WIN_1_VTX, width, height);
		m_rGameLib.SetVtxUV(TIME_LIMIT_WIN_1_VTX, texPos[TIME_LIMIT_WIN_1_VTX].x / HomeTextureWidth, (texPos[TIME_LIMIT_WIN_1_VTX].x + width) / HomeTextureWidth,
							texPos[TIME_LIMIT_WIN_1_VTX].y / HomeTextureHeight, (texPos[TIME_LIMIT_WIN_1_VTX].y + height) / HomeTextureHeight);
	}

	// 戦艦選択ボタンVertex作成ブロック
	{
		float width	 = 100.f;
		float height = 250.f;
		DWORD   BrightnessVal = 0xff505050;

		// 天龍ボタン
		m_rGameLib.CreateVtx(TENRYU_BTN_VTX, width, height);
		m_rGameLib.SetVtxColor(TENRYU_BTN_VTX, BrightnessVal);
		m_rGameLib.SetVtxUV(TENRYU_BTN_VTX, texPos[TENRYU_BTN_VTX].x / HomeTextureWidth, (texPos[TENRYU_BTN_VTX].x + width) / HomeTextureWidth,
							texPos[TENRYU_BTN_VTX].y / HomeTextureHeight, (texPos[TENRYU_BTN_VTX].y + height) / HomeTextureHeight);

		// 峯風ボタン
		m_rGameLib.CreateVtx(MINEKAZE_BTN_VTX, width, height);
		m_rGameLib.SetVtxColor(MINEKAZE_BTN_VTX, BrightnessVal);
		m_rGameLib.SetVtxUV(MINEKAZE_BTN_VTX, texPos[MINEKAZE_BTN_VTX].x / HomeTextureWidth, (texPos[MINEKAZE_BTN_VTX].x + width) / HomeTextureWidth,
							texPos[MINEKAZE_BTN_VTX].y / HomeTextureHeight, (texPos[MINEKAZE_BTN_VTX].y + height) / HomeTextureHeight);

		// 金剛ボタン
		m_rGameLib.CreateVtx(KONGOU_BTN_VTX, width, height);
		m_rGameLib.SetVtxColor(KONGOU_BTN_VTX, BrightnessVal);
		m_rGameLib.SetVtxUV(KONGOU_BTN_VTX, texPos[KONGOU_BTN_VTX].x / HomeTextureWidth, (texPos[KONGOU_BTN_VTX].x + width) / HomeTextureWidth,
							texPos[KONGOU_BTN_VTX].y / HomeTextureHeight, (texPos[KONGOU_BTN_VTX].y + height) / HomeTextureHeight);
	}

	// 軍艦情報背景ウィンドウVertex作成ブロック
	{
		float width  = 850.f;
		float height = 550.f;

		// 天龍シルエット
		m_rGameLib.CreateVtx(SHIP_INFO_BG_TENRYU_VTX, width, height);
		m_rGameLib.SetVtxUV(SHIP_INFO_BG_TENRYU_VTX, texPos[SHIP_INFO_BG_TENRYU_VTX].x / HomeTextureWidth, (texPos[SHIP_INFO_BG_TENRYU_VTX].x + width) / HomeTextureWidth,
							texPos[SHIP_INFO_BG_TENRYU_VTX].y / HomeTextureHeight, (texPos[SHIP_INFO_BG_TENRYU_VTX].y + height) / HomeTextureHeight);

		// 峯風シルエット
		m_rGameLib.CreateVtx(SHIP_INFO_BG_MINEKAZE_VTX, width, height);
		m_rGameLib.SetVtxUV(SHIP_INFO_BG_MINEKAZE_VTX, texPos[SHIP_INFO_BG_MINEKAZE_VTX].x / HomeTextureWidth, (texPos[SHIP_INFO_BG_MINEKAZE_VTX].x + width) / HomeTextureWidth,
							texPos[SHIP_INFO_BG_MINEKAZE_VTX].y / HomeTextureHeight, (texPos[SHIP_INFO_BG_MINEKAZE_VTX].y + height) / HomeTextureHeight);

		// 金剛シルエット
		m_rGameLib.CreateVtx(SHIP_INFO_BG_KONGOU_VTX, width, height);
		m_rGameLib.SetVtxUV(SHIP_INFO_BG_KONGOU_VTX, texPos[SHIP_INFO_BG_KONGOU_VTX].x / HomeTextureWidth, (texPos[SHIP_INFO_BG_KONGOU_VTX].x + width) / HomeTextureWidth,
							texPos[SHIP_INFO_BG_KONGOU_VTX].y / HomeTextureHeight, (texPos[SHIP_INFO_BG_KONGOU_VTX].y + height) / HomeTextureHeight);
	}
}

}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
