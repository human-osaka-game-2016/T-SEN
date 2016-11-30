/**
* @file		Vertex.cpp
* @brief	Vertexクラス実装
* @author	haga
*/

#include "Vertex.h"

// コンストラクタ
Vertex::Vertex(float width, float height, float depth, float tuMin, float tuMax, float tvMin, float tvMax) 
	: m_pD3Device(GraphicsDevice::GetInstance().GetDevice())
	, m_VtxWidth(width)
	, m_VtxHeight(height)
	, m_VtxDepth(depth)
	, m_TuMin(tuMin)
	, m_TuMax(tuMax)
	, m_TvMin(tvMin)
	, m_TvMax(tvMax)
{
	for (int i = 0; i < 4;i++)
	{
		m_Color[i] = 0xFFFFFFFF;
	}
}

// デストラクタ
Vertex::~Vertex()
{
}

// 描画(XY座標で考える場合)
void Vertex::Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{
	CUSTOMVERTEX vtex[] = {
		{		0.0f,		 0.0f, m_VtxDepth, 1.0f, m_Color[0], m_TuMin, m_TvMin },
		{ m_VtxWidth,		 0.0f, m_VtxDepth, 1.0f, m_Color[1], m_TuMax, m_TvMin },
		{ m_VtxWidth, m_VtxHeight, m_VtxDepth, 1.0f, m_Color[2], m_TuMax, m_TvMax },
		{		0.0f, m_VtxHeight, m_VtxDepth, 1.0f, m_Color[3], m_TuMin, m_TvMax },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
	}

	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}

// 描画 XZ座標で考える場合
void Vertex::Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ)
{
	CUSTOMVERTEX vtex[] = {
		{		0.0f, m_VtxHeight, m_VtxDepth, 1.0f, m_Color[0], m_TuMin, m_TvMax },
		{ m_VtxWidth, m_VtxHeight, m_VtxDepth, 1.0f, m_Color[1], m_TuMax, m_TvMax },
		{ m_VtxWidth, m_VtxHeight,		 0.0f, 1.0f, m_Color[2], m_TuMax, m_TvMin },
		{		0.0f, m_VtxHeight,		 0.0f, 1.0f, m_Color[3], m_TuMin, m_TvMin },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
		vtex[i].z += posZ;
	}

	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}

// 描画(中心に座標を合わせる)
void Vertex::DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{
	CUSTOMVERTEX vtex[] = {
		{ -m_VtxWidth / 2.0f, -m_VtxHeight / 2.0f, m_VtxDepth, 1.0f, m_Color[0], m_TuMin, m_TvMin },
		{  m_VtxWidth / 2.0f, -m_VtxHeight / 2.0f, m_VtxDepth, 1.0f, m_Color[1], m_TuMax, m_TvMin },
		{  m_VtxWidth / 2.0f,  m_VtxHeight / 2.0f, m_VtxDepth, 1.0f, m_Color[2], m_TuMax, m_TvMax },
		{ -m_VtxWidth / 2.0f,  m_VtxHeight / 2.0f, m_VtxDepth, 1.0f, m_Color[3], m_TuMin, m_TvMax },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
	}
	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}


// 描画(中心に座標を合わせる)引数にZ座標追加
void Vertex::DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ)
{

	CUSTOMVERTEX vtex[] = {
		{ -m_VtxWidth / 2.0f, m_VtxHeight,  m_VtxDepth / 2.0f, 1.0f, m_Color[0], m_TuMin, m_TvMax },
		{  m_VtxWidth / 2.0f, m_VtxHeight,  m_VtxDepth / 2.0f, 1.0f, m_Color[1], m_TuMax, m_TvMax },
		{  m_VtxWidth / 2.0f, m_VtxHeight, -m_VtxDepth / 2.0f, 1.0f, m_Color[2], m_TuMax, m_TvMin },
		{ -m_VtxWidth / 2.0f, m_VtxHeight, -m_VtxDepth / 2.0f, 1.0f, m_Color[3], m_TuMin, m_TvMin },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
		vtex[i].z += posZ;
	}
	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}

// UVスクロールを行う関数
void Vertex::ScrollUV(float scrollSpeedTu, float scrollSpeedTv)
{
	m_TuMin += scrollSpeedTu;
	m_TuMax += scrollSpeedTu;
	m_TvMin += scrollSpeedTv;
	m_TvMax += scrollSpeedTv;
}

// サイズをセットする関数
void Vertex::SetSize(float vtxWidth, float vtxHeight)
{
	m_VtxWidth = vtxWidth;
	m_VtxHeight = vtxHeight;
}

// tu,tv値を設定する関数
void Vertex::SetTuTvVal(float tuMin, float tuMax, float tvMin, float tvMax)
{
	m_TuMin = tuMin;
	m_TuMax = tuMax;
	m_TvMin = tvMin;
	m_TvMax = tvMax;
}

// 色を設定する関数
void Vertex::SetColor(DWORD color)
{
	for (int i = 0; i < 4; i++)
	{
		m_Color[i] = color;
	}
}
