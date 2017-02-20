//==================================================================================================================================//
//!< @file		TextureManager.h
//!< @brief		TextureManagerクラス実装
//!< @author	haga
//==================================================================================================================================//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <d3dx9.h>
#include <d3d9.h>
#include <map>

/**テクスチャーを管理するクラス*/
class TextureManager
{

public:
	/**Constructor*/
	TextureManager();

	/**Destructor*/
	~TextureManager();

	/**
	* テクスチャーを読み込む関数.
	* @param[in] key			登録するキー、またはID(enumで作成を想定)
	* @param[in] pFilepath		ファイルへのパス
	*/
	void Load(int key, TCHAR* pFilePath);

	/**
	* テクスチャーを詳細設定を行って読み込む関数.
	* @param[in] key			登録するキー、またはID(enumで作成を想定)
	* @param[in] pFilepath		ファイルへのパス
	* @param[in] alpha			アルファ値
	* @param[in] red			色のR値 255
	* @param[in] green			色のG値 255
	* @param[in] blue			色のB値 255
	* @param[in] isPowerTwo		テクスチャーのサイズが２のべき乗ならtrue,違うならfalse
	*/
	void LoadEx(int key, TCHAR* pFilePath, int alpha = 255, int red = 0, int green = 0, int blue = 0, bool isPowerTwo = false);

	/**
	* テクスチャーのアドレスを取得する関数
	* @param[in] key			登録したキー
	* @return m_pTexture[key]	キーに対応したテクスチャーへのポインタ
	*/
	inline LPDIRECT3DTEXTURE9 GetTex(int key){ return m_pTexture[key]; }

	/**
	* テクスチャー解放関数
	* @param[in] key			登録したキー
	*/
	void Release(int key);

	/**テクスチャーをすべて解放する関数*/
	void ReleaseALL();

private:
	IDirect3DDevice9*				  m_pD3Device;		//!< DirectXデバイス
	std::map<int, LPDIRECT3DTEXTURE9> m_pTexture;		//!< テクスチャーへのポインタを格納するmap

};

#endif	// TEXTURE_MANAGER_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
