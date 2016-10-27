/**
* @file TextureManager.h
* @brief テクスチャーを管理するクラスのh
* @author haga
*/
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <d3dx9.h>
#include <d3d9.h>
#include "GraphicsDevice.h"
#include <map>

class TextureManager
{
private:
	IDirect3DDevice9*				  m_pD3Device;	//!< デバイス
	std::map<int, LPDIRECT3DTEXTURE9> m_texture;	//!< テクスチャー情報を格納する変数

public:
	/**コンストタクタ*/
	TextureManager();

	/**デストラクタ*/
	~TextureManager();

	/**
	* テクスチャーを読み込む関数.
	* @param[in] key		登録するキー、またはID(enumで作成を想定)
	* @param[in] filepath   ファイル名
	*/
	void Load(int key,char* filePath); 

	/**
	* テクスチャーを詳細設定して読み込む関数.
	* @param[in] key		登録するキー、またはID(enumで作成を想定)
	* @param[in] filepath   ファイル名
	* @param[in] a			アルファ値
	* @param[in] r			色のR値 255
	* @param[in] g			色のG値 255
	* @param[in] b			色のB値 255
	* @param[in] size		テクスチャーのサイズが２のべき乗ならtrue,違うならfalse
	*/
	void LoadEx(int key, char* filePath, int a = 255, int r = 0, int g = 0, int b = 0, bool size = false);

	/**
	* テクスチャーのアドレスを取得する関数
	* @param[in] key	登録したキー
	*/
	LPDIRECT3DTEXTURE9 GetTex(int key);

	/**
	* テクスチャー解放関数
	* @param[in] key	登録したキー
	*/
	void Release(int key);

	/**
	* テクスチャーをすべて解放する関数
	*/
	void ReleaseALL();

};

#endif	// TEXTURE_MANAGER_H
