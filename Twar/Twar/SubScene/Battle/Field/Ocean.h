/**
* @file Ocean.h
* @brief Oceanクラスヘッダ
* @author Matsuda
*/
#ifndef OCEAN_H
#define OCEAN_H

#include <d3dx9.h>


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
	D3DXVECTOR3       m_Pos;
	float             m_Scale;
};

#endif//OCEANE_H
