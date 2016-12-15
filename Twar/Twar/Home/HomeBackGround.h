/**
* @file		HomeBackground.h
* @brief	HomeBackgroundクラスヘッダ
* @author	haga
*/

#ifndef HOME_BACKGROUND_H
#define HOME_BACKGROUND_H

#include <d3dx9.h>

/**
* Homeシーン(鎮守府)の背景を描画するクラス
*/
class HomeBackground
{
public:
	/**コンストラクタ*/
	HomeBackground();

	/**デストラクタ*/
	~HomeBackground();

	/**描画関数*/
	void Draw();

private:
	D3DXVECTOR2			m_Pos;		//!< 位置座標

};

#endif	// HOME_BACKGROUND_H
