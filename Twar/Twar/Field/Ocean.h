/**
* @file  Ocean.h
* @brief Oceanクラスのヘッダー
* @author Matsuda
*/
#ifndef OCEAN_H
#define OCEAN_H

#include <d3dx9.h>

class GameLib;
class XFile;
class CameraController;

/**
*Oceanクラス
*/

class Ocean
{
public:
	/**コンストラクタ*/
	Ocean();

	/**デストラクタ*/
	~Ocean();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

private:
	GameLib*          m_pGameLib;
	XFile*			  m_xFile;
	CameraController*       m_pCameraController;
	D3DXVECTOR3       m_Pos;
	float             m_Scale;
};

#endif//OCEANE_H
