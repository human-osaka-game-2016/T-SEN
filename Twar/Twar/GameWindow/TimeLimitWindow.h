//==================================================================================================================================//
//!< @file		TimeLimitWindow.h
//!< @brief		TimeLimitWindowクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef TIME_LIMIT_WINDOW_H
#define TIME_LIMIT_WINDOW_H

#include "GameWindow.h"

class GameDataManager;
class Font;

/***
* モンスター撃退日数期限を表示するウィンドウ
*/
class TimeLimitWindow : public GameWindow
{

public:
	/**
	* Constructor
	* @param	 rPos			位置座標
	* @param	 texID			TextureID
	* @param	 vtxID			VertexID
	*/
	TimeLimitWindow(const D3DXVECTOR2& rPos, int texID, int vtxID);

	/**Destructor*/
	~TimeLimitWindow();

	/**コントロール関数*/
	virtual void Control()override;

	/**描画関数*/
	virtual void Draw()override;

};

#endif	// TIME_LIMIT_WINDOW_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
