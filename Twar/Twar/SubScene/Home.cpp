/**
* @file		Home.cpp
* @brief	Homeクラス実装
* @author	haga
*/

//------------------------------------------------------------------------------------------------------------//
//Includes
//------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "../GameData/SaveDataManager.h"
#include "Home.h"
#include "../Home/HomeBackGround.h"
#include "../Home/HomeMenu.h"

//-----------------------------------------------------------------------------------------------------------//
//Namespace
//-----------------------------------------------------------------------------------------------------------//

namespace sub_scene
{

//----------------------------------------------------------------------------------------------------------//
//Public functions
//----------------------------------------------------------------------------------------------------------//

Home::Home(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	: SubScene(pGameDataManager, pGameTimer, pSaveDataManager)
	, m_pBackground(new HomeBackground())
	, m_pHomeMenu(new HomeMenu())
	, m_CurrentState(Home::NOMAL)
{
	InitHomeScene();
}

Home::~Home()
{
	m_rGameLib.ReleaseAllVertex();
	m_rGameLib.ReleaseAllTex();
	delete m_pHomeMenu;
	delete m_pBackground;
}

SUBSCENE_ID Home::Control()
{
	switch(m_CurrentState)
	{
	case Home::BATTLE_START:
		return SUBSCENE_ID::BATTLE;

		break;

	case Home::WORLD_MAP_START:
		break;

	case Home::SHIPYARD_START:
		break;

	case Home::NOMAL:
		m_CurrentState = m_pHomeMenu->Control();
		break;
	}

	return SUBSCENE_ID::HOME;
}

void Home::Draw()
{
	m_pBackground->Draw();
	m_pHomeMenu->Draw();
}

//-----------------------------------------------------------------------------------------------------------//
//Private functions
//-----------------------------------------------------------------------------------------------------------//

void Home::InitHomeScene()
{
	/**@todo 仮画像のﾊﾟｽにしておく*/
	m_rGameLib.LoadTexEx(Home::BACKGROUND_TEX, "../Resouce/tsentitle.png", 255, 0, 0, 0, false);
	m_rGameLib.LoadTexEx(Home::MENU_BTN_TEX, "../Resouce/title_button.png", 255, 0, 0, 0, false);
}

}
