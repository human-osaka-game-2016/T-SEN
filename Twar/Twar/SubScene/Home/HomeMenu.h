//==================================================================================================================================//
//!< @file		HomeMenu.h
//!< @brief		HomeMenuクラスヘッダ
//!< @author	haga
//==================================================================================================================================//


#ifndef HOME_MENU_H
#define HOME_MENU_H

#include <vector>
#include "Home.h"
#include "../../GameData/GameDataManager.h"
#include "../Battle/Ship/ShipManager.h"

class Button;

class HomeMenu
{

public:
	/**
	* Constructor
	* @param pDataManager GameDataManagerクラスのインスタンスへのポインタ
	*/
	explicit HomeMenu(GameDataManager* pDataManager);

	/**Destructor*/
	~HomeMenu();

	/**
	* コントロール関数.
	* @return	SubSceneのIDをかえす
	*/
	sub_scene::SUBSCENE_ID	Control();

	/**描画関数*/
	void Draw();

	/**
	* 現在選択している船のIDを取得する関数
	* @return 現在選択している船のID
	*/
	GameDataManager::SHIP_ID GetSelectShipID(){ return m_SelectShipID; }

private:
	GameDataManager*			m_pDataManager;				//!< GameDataManagerクラスのインスタンスへのポインタ
	Button*						m_pBattleButton;			//!< 戦闘開始ボタン
	Button*						m_pPoliticsButton;			//!< 政略ボタン
	std::vector<Button*>		m_pShipSelectButtons;		//!< 軍艦選択ボタン
	GameDataManager::SHIP_ID	m_SelectShipID;				//!< 現在選択している船のID

	/**
	* プレイヤーが選択した軍艦のIDを返す関数
	* @return 選択した軍艦のID
	*/
	GameDataManager::SHIP_ID	SelectShip();

	/**
	* プレイヤーが選択したSubSceneのIDを返す関数
	* @return 選択したSubSceneのID
	*/
	sub_scene::SUBSCENE_ID SelectSubScene();
};

#endif // HOME_MENU_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
