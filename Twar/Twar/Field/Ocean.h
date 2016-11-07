/**
* @file  Ocean.h
* @brief Oceanクラス実装
* @author Matsuda
*/
#ifndef OCEAN_H
#define OCEAN_H

#include <d3dx9.h>

class GameLib;
class XFile;

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
	D3DXVECTOR3       m_Pos;
	float             m_Scale;
};

#endif//OCEANE_H
