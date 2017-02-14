//==================================================================================================================================//
//!< @file		TextureManager.cpp
//!< @brief		TextureManagerクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "TextureManager.h"
#include "GraphicsDevice.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

TextureManager::TextureManager()
	: m_pD3Device(GraphicsDevice::GetInstance().GetDevice())
{}

TextureManager::~TextureManager()
{
	ReleaseALL();
}

void TextureManager::Load(int key, TCHAR* pFilePath)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	m_pTexture[key] = texture;
	if (FAILED(D3DXCreateTextureFromFile(m_pD3Device, pFilePath, &m_pTexture[key])))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
	}
	else
	{
		// 読み込み成功。 チェック用空処理
	}
}

void TextureManager::LoadEx(int key, TCHAR* pFilePath, int alpha, int red, int green, int blue, bool isPowerTwo)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	m_pTexture[key] = texture;
	if(isPowerTwo)
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3Device,				//	インターフェイスへのポインタ
			pFilePath,					//	画像ファイル名
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(alpha, red, green, blue),
			NULL,
			NULL,
			&m_pTexture[key]
			)))
		{
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
		}
		else
		{
			// 画像の読み込み成功。 チェック用空処理
		}
	}
	else			//２のべき乗じゃない場合
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3Device,
			pFilePath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			D3DCOLOR_ARGB(alpha, red, green, blue),
			NULL, NULL,
			&m_pTexture[key])))
		{
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
		}
		else
		{
			// 画像の読み込み成功。 チェック用空処理
		}
	}
}

void TextureManager::Release(int key)
{
	m_pTexture[key]->Release();
	m_pTexture.erase(key);
}

void TextureManager::ReleaseALL()
{
	for (auto& itr = m_pTexture.begin(); itr != m_pTexture.end(); ++itr)
	{
		if (itr->second)
		{
			itr->second->Release();
			itr->second = NULL;
		}
		else
		{
			// 処理続行。 チェック用空処理
		}
	}

	m_pTexture.clear();
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
