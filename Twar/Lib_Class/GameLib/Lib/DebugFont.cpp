/**
* @file DebugFont.cpp
* @brief デバックで使用するフォントのクラス
* @author haga
*/
#include "DebugFont.h"


DebugFont::DebugFont(INT height, UINT width, D3DCOLOR color):
m_pD3Device(GraphicsDevice::GetInstance().GetDevice()),
m_pFont(NULL),
m_height(height),
m_width(width),
m_color(color)
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


DebugFont::~DebugFont()
{
	if (m_pFont != NULL)
	{
		Release();
	}
}

// 文字描画関数
void DebugFont::Draw(LPCTSTR pString, D3DXVECTOR2 pos)
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
		m_color);						// 色
}

// メモリ開放関数
void DebugFont::Release()
{
	m_pFont->Release();
	m_pFont = NULL;
}