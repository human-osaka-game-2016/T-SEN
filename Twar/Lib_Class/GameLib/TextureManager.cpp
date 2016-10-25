/**
* @file TextureManager.h
* @brief テクスチャーを管理するクラスのh
* @author haga
*/

#include "TextureManager.h"


TextureManager::TextureManager():
m_pD3Device(GraphicsDevice::GetInstance().GetDevice())
{
}


TextureManager::~TextureManager()
{
	ReleaseALL();
}

void TextureManager::Load(int key, char* filePath)
{
	LPDIRECT3DTEXTURE9 tex = NULL;
	m_texture[key] = tex;
	if (FAILED(D3DXCreateTextureFromFile(m_pD3Device, filePath, &m_texture[key])))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
	}

}

void TextureManager::LoadEx(int key, char* filePath, int a, int r, int g, int b, bool size)
{
	LPDIRECT3DTEXTURE9 tex = NULL;
	m_texture[key] = tex;
	if (size)
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3Device,			//	インターフェイスへのポインタ
			filePath,					//	画像ファイル名
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(a, r, g, b),
			NULL,
			NULL,
			&m_texture[key]
			)))
		{
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
		}
	}
	else			//２のべき乗じゃないのなら
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3Device,
			filePath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			D3DCOLOR_ARGB(a, r, g, b),
			NULL, NULL,
			&m_texture[key])))
		{
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
		}

	}
}

LPDIRECT3DTEXTURE9 TextureManager::GetTex(int key)
{
	return m_texture[key];
}

void TextureManager::Release(int key)
{
	m_texture[key]->Release();
	m_texture.erase(key);
}

void TextureManager::ReleaseALL()
{
	for (auto itr = m_texture.begin(); itr != m_texture.end(); ++itr)
	{
		if (itr->second)
		{
			itr->second->Release();
			itr->second = NULL;
		}
	}

	m_texture.clear();
}