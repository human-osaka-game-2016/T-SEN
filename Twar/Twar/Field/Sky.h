/**
* @file  Sky.h
* @brief Skyクラスヘッダ
* @author Matsuda
*/
#ifndef SKY_H
#define SKY_H

#include <d3dx9.h>

class GameLib;
class XFile;

/**
*Skyクラス
*/
class Sky
{
public:
	/**コンストラクタ*/
	Sky();

	/**デストラクタ*/
	~Sky();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

private:
	GameLib*          m_pGameLib;
	XFile*			  m_pXFile;
	D3DXVECTOR3       m_Pos;
	float             m_Scale;
};
#endif//SKY_H

