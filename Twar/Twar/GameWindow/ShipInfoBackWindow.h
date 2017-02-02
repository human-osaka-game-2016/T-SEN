//==================================================================================================================================//
//!< @file		ShipInfoBackWindow.h
//!< @brief		ShipInfoBackWindowクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef SHIP_INFO_BACK_WINDOW_H
#define SHIP_INFO_BACK_WINDOW_H

#include "GameWindow.h"
#include "../SubScene/Battle/Ship/ShipManager.h"

class HomeMenu;

class ShipInfoBackWindow : public GameWindow
{

public:
	/**
	* Constructor
	* @param		rPos				位置座標
	* @param		texID				TextureID
	* @param		tenryuVtxID			天龍のシルエットのVertexID
	* @param		minekazeVtxID		峯風のシルエットのVertexID
	* @param		kongouVtxID			金剛のシルエットのVertexID
	* @param[in]	pHomeMenu			HomeMenuクラスのインスタンスへのポインタ
	*/
	ShipInfoBackWindow(const D3DXVECTOR2& rPos, int texID, int tenryuVtxID, int minekazeVtxID, int kongouVtxID, HomeMenu* pHomeMenu);

	/**Desutructor*/
	virtual ~ShipInfoBackWindow();

	/**コントロール関数*/
	virtual void Control()override;

	/**描画関数*/
	virtual void Draw()override;

private:
	HomeMenu*				m_pHomeMenu;			//!< HomeMenuクラスのインスタンスへのポインタ
	int						m_MinekazeVtxID;		//!< 峯風のシルエットのVertexID
	int						m_KongouVtxID;			//!< 金剛のシルエットのVertexID
	ShipManager::SHIP_ID	m_CurrentID;			//!< 現在選択している船のID

};

#endif	// SHIP_INFO_BACK_WINDOW_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
