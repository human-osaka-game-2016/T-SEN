/**
* @file Font.cpp
* @brief フォントを扱うクラスのcpp
* @author haga
*/
#include "../Font/Font.h"

Font::Font(IDirect3DDevice9*	pD3Device) :
m_pD3Device(pD3Device),
m_pFont(NULL),
m_height(20),
m_width(10)
{
	if (FAILED(D3DXCreateFont(m_pD3Device,
		m_height,
		m_width,
		FW_REGULAR,
		NULL,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		TEXT("ＭＳ　Ｐゴシック"),
		&m_pFont)))
	{
		MessageBox(NULL,"フォントクラスを作成できません","Error",MB_OK);
	}
}

// コンストラクタ 文字の大きさを指定する場合に使用
Font::Font(IDirect3DDevice9*	pD3Device,INT height, INT	width) :
m_pD3Device(pD3Device),
m_pFont(NULL),
m_height(height),
m_width(width)
{
	if (FAILED(D3DXCreateFont(m_pD3Device,
		m_height,
		m_width,
		FW_REGULAR,
		NULL,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		TEXT("ＭＳ　Ｐゴシック"),
		&m_pFont)))
	{
		MessageBox(NULL, "フォントクラスを作成できません", "Error", MB_OK);
	}
}


Font::~Font()
{
	if (m_pFont != NULL)m_pFont->Release();
}

// テキストを表示する関数
void Font::Draw(LPCTSTR pString, D3DXVECTOR2 pos)
{
	RECT rc;
	D3DXFONT_DESC desc;
	m_pFont->GetDesc(&desc);

	rc.left = (LONG)pos.x;
	rc.top = (LONG)pos.y;
	rc.right = (LONG)pos.x + desc.Width * strlen(pString);
	rc.bottom = (LONG)pos.y + desc.Height * strlen(pString);
	m_pFont->DrawText(
		NULL,							// NULL
		pString,						// 描画テキスト
		-1,								// 全て表示
		&rc,							// 表示範囲
		DT_LEFT,						// 左寄せ
		D3DCOLOR_XRGB(255, 255, 255));	// 白色
}

// テキストを表示する関数(色と文字寄せを変えれる)
void Font::Draw(LPCTSTR pString, D3DXVECTOR2 pos, DWORD format, D3DCOLOR color)
{
	RECT rc;
	D3DXFONT_DESC desc;
	m_pFont->GetDesc(&desc);

	rc.left = (LONG)pos.x;
	rc.top = (LONG)pos.y;
	rc.right = (LONG)pos.x + desc.Width * strlen(pString);
	rc.bottom = (LONG)pos.y + desc.Height * strlen(pString);

	m_pFont->DrawText(
		NULL,		// NULL 
		pString,	// 描画テキスト
		-1,			// 全て表示
		&rc,		// 表示範囲
		format,		// 文字寄せ
		color);		// 文字の色
}

// 文字のフォントなどを再設定する関数
void Font::ReCreateFont(LPCTSTR pFacename, UINT weight, BOOL italic)
{
	// フォントを一度開放する
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	if (FAILED(D3DXCreateFont(m_pD3Device,
		m_height,
		m_width,
		weight,
		NULL,
		italic,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		pFacename,
		&m_pFont)))
	{
		MessageBox(NULL, "フォントクラスを作成できません", "Error", MB_OK);
	}
}