/**
* @file Texture.cpp
* @brief テクスチャーに関連するクラス.cpp
* @author haga
*/
#include <d3dx9.h>
#include <d3d9.h>
#include "GraphicsDevice.h"
#include "Texture.h"

// コンストラクタ
Texture::Texture() :m_pTexture(NULL), m_pD3Device(GraphicsDevice::GetInstance().GetDevice())
{
}

// デストラクタ
Texture::~Texture()
{
	SAFE_RELEASE(m_pTexture);
}

// 画像読み込み簡易版
HRESULT Texture::LoadTex(char* text)
{
	if (FAILED(D3DXCreateTextureFromFile(m_pD3Device, text, &m_pTexture)))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

// 画像読み込み詳細設定版
HRESULT Texture::LoadTexEx(char* text, int a, int r, int g, int b, bool size)
{
	if (size)
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3Device,			//	インターフェイスへのポインタ
			text,					//	画像ファイル名
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
			&m_pTexture
			)))
		{
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
			return E_FAIL;
		}
	}
	else			//２のべき乗じゃないのなら
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3Device,
			text,
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
			&m_pTexture)))
		{
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
			return E_FAIL;
		}

	}
	return S_OK;
}

// 描画
void Texture::RenderTex(CUSTOMVERTEX* setdraw)
{
	m_pD3Device->SetTexture(0, m_pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,setdraw,sizeof(CUSTOMVERTEX));
}

// デバイスを取得する関数
void Texture::GetDevice()
{
	m_pD3Device = GraphicsDevice::GetInstance().GetDevice();
}

// メモリ開放する関数
void Texture::Release()
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
	}
}