/**
* @file  Sky.h
* @brief 空のh
* @author Matsuda
*/
#ifndef SKY_H
#define SKY_H

#include <d3dx9.h>
#include "GameLib/Lib/XFile.h"
#include "GameLib/Lib/GraphicsDevice.h"

class Sky
{
private:
	IDirect3DDevice9* m_pD3Device;
	XFile			  m_xFile;
	D3DXVECTOR3       m_Pos;
	float             m_Scale;
public:
	/**コンストラクタ*/
	Sky();

	/**デストラクタ*/
	~Sky();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();
};
#endif