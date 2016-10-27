/**
* @file DebugFont.h
* @brief デバックで使用するフォントのクラス
* @author haga
*/

#ifndef DEBUG_FONT_H
#define DEBUG_FONT_H

#include<d3dx9.h>
#include"GraphicsDevice.h"

class DebugFont
{
private:
	IDirect3DDevice9*	m_pD3Device;		//!< Direct3Dのデバイス
	LPD3DXFONT			m_pFont;			//!< ID3DXFontインターフェイスへのポインタ
	INT					m_height;			//!< 文字の高さ
	UINT				m_width;			//!< 文字の幅
	D3DCOLOR			m_color;			//!< 文字の色

public:
	/**コンストラクタ*/
	DebugFont(INT height = 20, UINT width = 10, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

	/**デストラクタ*/
	~DebugFont();

	/**
	* テキストを描画する関数<br>
	* こちらは文字の色を変更できる
	* @param[in] pString	表示したい文字列
	* @param[in] pos		テキストを表示したい座標
	* @param[in] color		文字の色
	*/
	void Draw(LPCTSTR pString, D3DXVECTOR2 pos);

	/**mメモリ開放関数*/
	void Release();

	/**
	* 1文字の高さを取得する関数.
	* @return m_height	文字の高さ
	*/
	INT	 GetFontHeight(){ return m_height; }
};

#endif // DEBUG_FONT_H
