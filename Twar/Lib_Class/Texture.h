/**
* @file Texture.h
* @brief テクスチャーに関連するクラス.h
* @author haga
*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3dx9.h>
#include <d3d9.h>
#include "GraphicsDevice.h"

/**
* カスタムバーテックス構造体.
*/
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;	//!< 座標系
	DWORD	color;			//!< 色
	FLOAT	tu, tv;			//!< テクスチャーのtu,tv値
};

/**
* テクスチャーを管理するクラス.
*/
class Texture
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;		//!< テクスチャーを格納する変数
	IDirect3DDevice9*	m_pD3Device;	//!< デバイス

public:
	/**コンストラクタ*/
	Texture();
	/**デストラクタ*/
	~Texture();

	/**
	* 画像読み込み簡易版.
	* @param[in] text   画像ファイルの名前
	* @retval S_OK		画像読み込み成功
	* @retval E_FAIL	画像読み込み失敗
	*/
	HRESULT LoadTex(char* text);

	/**
	* 画像読み込み詳細設定版.
	* @param[in] text 画像ファイルの名前
	* @param[in] a	  アルファ値
	* @param[in] r	  色のr値
	* @param[in] g	  色のg値
	* @param[in] b	  色のb値
	* @param[in] size 2のべき乗サイズかどうか
	* @retval S_OK	  画像読み込み成功
	* @retval E_FAIL  画像読み込み失敗
	*/
	HRESULT LoadTexEx(char* text,int a,int r,int g,int b,bool size);

	/**
	* 描画.
	* @param[in] setdraw
	*/
	void RenderTex(CUSTOMVERTEX* setdraw);

	/**
	* デバイスを取得する関数<br>
	* staticでCTextureを使う場合.
	*/
	void GetDevice();

	/**
	* テクスチャーを開放する関数<br>
	*/
	void Release();

	/**
	* テクスチャーを格納しているかを確認.
	* @return m_pTexture テクスチャーを格納する変数
	*/
	LPDIRECT3DTEXTURE9 GetStateTex(){ return m_pTexture; }

};

#endif		// TEXTURE_H