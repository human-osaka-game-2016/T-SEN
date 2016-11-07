/**
* @file  Ocene.h
* @brief 海のh
* @author Matsuda
*/
#ifndef OCENE_H
#define OCENE_H

#include <d3dx9.h>
#include "GameLib/Lib/XFile.h"
#include "GameLib/Lib/GraphicsDevice.h"

class Ocene
{
private:
	IDirect3DDevice9* m_pD3Device;
	XFile			  m_xFile;
	D3DXVECTOR3       m_Pos;
	float             m_Scale;
public:
	/**コンストラクタ*/
	Ocene();

	/**デストラクタ*/
	~Ocene();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();
};

#endif