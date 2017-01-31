//==================================================================================================================================//
//!< @file		ShipInfoWindow.h
//!< @brief		ShipInfoWindowクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef SHIP_INFO_WINDOW_H
#define SHIP_INFO_WINDOW_H

#include "GameWindow.h"
#include "../SubScene/Battle/Ship/ShipManager.h"

class GameDataManager;
class HomeMenu;
class Font;

class ShipInfoWindow : public GameWindow
{

public:
	/**
	* Constructor
	* @param		rPos				位置座標
	* @param		texID				TextureID
	* @param		winVtxID			WindowsのVertexID
	* @param		textVtxID			TextのVertexID
	* @param[in]	pDataManager		GameDataManagerクラスのインスタンスへのポインタ
	* @param[in]	pHomeMenu			HomeMenuクラスのインスタンスへのポインタ
	*/
	ShipInfoWindow(const D3DXVECTOR2& rPos, int texID, int winVtxID, int textVtxID, GameDataManager* pDatamanager, HomeMenu* pHomeMenu);

	/**Destructor*/
	virtual ~ShipInfoWindow();

	/**コントロール関数*/
	virtual void Control()override;

	/**描画関数*/
	virtual void Draw()override;

private:
	enum SHIP_INFO_TEXT
	{
		NAME,			// 軍艦の種類
		DURABILITY,		// 耐久値  
		AGGRESSIVITY,	// 攻撃力
		SPEED,			// 速さ
		TEXT_MAX
	};
	int						m_TextVtxID;			//!< テキストのVertexID
	GameDataManager*		m_pDatamanager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	HomeMenu*				m_pHomeMenu;			//!< HomeMenuクラスのインスタンスへのポインタ
	Font*					m_pFont;				//!< Fontクラスのインスタンスへのポインタ
	ShipManager::SHIP_ID	m_CurrentID;			//!< 現在選択している船のID

};

#endif	// SHIP_INFO_WINDOW_H 

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//