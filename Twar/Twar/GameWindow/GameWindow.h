//==================================================================================================================================//
//!< @file		GameWindow.h
//!< @brief		GameWindowクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <d3dx9.h>

/**
* ゲーム中に表示するウィンドウの基底クラス
*/
class GameWindow
{

public:
	/**
	* Constructor
	* @param rPos	位置座標
	* @param texID	TextureID
	* @param vtxID	VertexID
	*/
	GameWindow(const D3DXVECTOR2& rPos, int texID, int vtxID);

	/**Destructor*/
	virtual ~GameWindow() = default;

	/**コントロール関数*/
	virtual void Control() = 0;

	/**描画関数*/
	virtual void Draw() = 0;

protected:
	D3DXVECTOR2			m_Pos;		//!< 位置座標
	int					m_TexID;	//!< TextureID
	int					m_VtxID;	//!< VertexID

};

#endif	// GAME_WINDOW_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//

