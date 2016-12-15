/**
* @file		Vertex.cpp
* @brief	Vertexクラス実装
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "Vertex.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

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

// 2Dの通常描画
void Vertex::Draw2D(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
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

// 3D空間におけるXY平面ポリゴンの描画関数
void Vertex::Draw3DXY(LPDIRECT3DTEXTURE9 pTexture)
{
	CUSTOMVERTEX3D vtex[] = {
		{		0.0f, m_VtxHeight, m_VtxDepth, m_Color[0], m_TuMin, m_TvMin },
		{ m_VtxWidth, m_VtxHeight, m_VtxDepth, m_Color[1], m_TuMax, m_TvMin },
		{ m_VtxWidth,		 0.0f, m_VtxDepth, m_Color[2], m_TuMax, m_TvMax },
		{		0.0f,		 0.0f, m_VtxDepth, m_Color[3], m_TuMin, m_TvMax },
	};

	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX3D));
}

// 3D空間におけるXZ平面ポリゴンの描画関数
void Vertex::Draw3DXZ(LPDIRECT3DTEXTURE9 pTexture)
{
	CUSTOMVERTEX3D vtex[] = {
		{		0.0f, m_VtxHeight, m_VtxDepth, m_Color[0], m_TuMin, m_TvMin },
		{ m_VtxWidth, m_VtxHeight, m_VtxDepth, m_Color[1], m_TuMax, m_TvMin },
		{ m_VtxWidth, m_VtxHeight,		 0.0f, m_Color[2], m_TuMax, m_TvMax },
		{		0.0f, m_VtxHeight,		 0.0f, m_Color[3], m_TuMin, m_TvMax },
	};

	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX3D));
}

// 2D描画(中心に座標を合わせる)
void Vertex::Draw2DCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
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

//  3D空間におけるXY平面ポリゴンの描画関数(中心に座標を合わせる)
void Vertex::Draw3DXYCenterPos(LPDIRECT3DTEXTURE9 pTexture)
{
	CUSTOMVERTEX3D vtex[] = {
		{ -m_VtxWidth / 2.0f,  m_VtxHeight / 2.0f, m_VtxDepth, m_Color[0], m_TuMin, m_TvMin },
		{  m_VtxWidth / 2.0f,  m_VtxHeight / 2.0f, m_VtxDepth, m_Color[1], m_TuMax, m_TvMin },
		{  m_VtxWidth / 2.0f, -m_VtxHeight / 2.0f, m_VtxDepth, m_Color[2], m_TuMax, m_TvMax },
		{ -m_VtxWidth / 2.0f, -m_VtxHeight / 2.0f, m_VtxDepth, m_Color[3], m_TuMin, m_TvMax },
	};


	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX3D));
}

// 3D空間におけるXZ平面ポリゴンの描画関数(中心に座標を合わせる)
void Vertex::Draw3DXZCenterPos(LPDIRECT3DTEXTURE9 pTexture)
{
	CUSTOMVERTEX3D vtex[] = {
		{ -m_VtxWidth / 2.0f, m_VtxHeight,  m_VtxDepth / 2.0f, m_Color[0], m_TuMin, m_TvMin },
		{  m_VtxWidth / 2.0f, m_VtxHeight,  m_VtxDepth / 2.0f, m_Color[1], m_TuMax, m_TvMin },
		{  m_VtxWidth / 2.0f, m_VtxHeight, -m_VtxDepth / 2.0f, m_Color[2], m_TuMax, m_TvMax },
		{ -m_VtxWidth / 2.0f, m_VtxHeight, -m_VtxDepth / 2.0f, m_Color[3], m_TuMin, m_TvMax },
	};

	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX3D));
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
