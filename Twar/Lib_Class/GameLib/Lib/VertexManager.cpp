/**
* @file		VertexManager.cpp
* @brief	VertexManagerクラス実装
* @author	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "VertexManager.h"

//------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//------------------------------------------------------------------------------------------------------------------------------------//

VertexManager::VertexManager()
{
}

VertexManager::~VertexManager()
{
	ReleaseALL();
}

// バーテックスクラスを作成し、登録する関数
void VertexManager::CreateVertex(int key, float width, float height, float depth,
	float tuMin, float tuMax, float tvMin, float tvMax)
{
	Vertex vtx(width, height, depth, tuMin, tuMax, tvMin, tvMax);

	m_Vertex[key] = vtx;
}

// 2Dの通常描画関数
void VertexManager::Draw2D(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{
	m_Vertex[key].Draw2D(pTexture, posX, posY);
}

// 3D空間におけるXY平面におけるポリゴンの通常描画関数
void VertexManager::Draw3DXY(int key, LPDIRECT3DTEXTURE9 pTexture)
{
	m_Vertex[key].Draw3DXY(pTexture);
}

// 3D空間におけるXZ平面におけるポリゴンの通常描画関数
void VertexManager::Draw3DXZ(int key, LPDIRECT3DTEXTURE9 pTexture)
{
	m_Vertex[key].Draw3DXZ(pTexture);
}

// 2Dの描画関数(中心に座標をあわせる)
void VertexManager::Draw2DCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{
	m_Vertex[key].Draw2DCenterPos(pTexture, posX, posY);
}

// 3D空間におけるXY平面ポリゴンの描画関数(中心に座標を合わせる)
void VertexManager::Draw3DXYCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture)
{
	m_Vertex[key].Draw3DXYCenterPos(pTexture);
}

// 3D空間におけるXZ平面ポリゴンの描画関数(中心に座標を合わせる)
void VertexManager::Draw3DXZCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture)
{
	m_Vertex[key].Draw3DXZCenterPos(pTexture);
}

// UVスクロールする関数
void VertexManager::ScrollUV(int key, float scrollSpeedTu, float scrollSpeedTv)
{
	m_Vertex[key].ScrollUV(scrollSpeedTu, scrollSpeedTv);
}

// サイズを変更する関数
void VertexManager::SetSize(int key, float width, float height, float depth)
{
	m_Vertex[key].SetSize(width, height);
}

// tu値とtv値を変更する関数
void VertexManager::SetTuTv(int key, float tuMin, float tuMax, float tvMin, float tvMax)
{
	m_Vertex[key].SetTuTvVal(tuMin, tuMax, tvMin, tvMax);
}

// 色を変更する関数
void VertexManager::SetColor(int key, DWORD color)
{
	m_Vertex[key].SetColor(color);
}

// バーテックスの横幅を取得する関数
float VertexManager::GetVtxWidth(int key)
{
	return m_Vertex[key].GetVtxWidth();
}

// バーテックスの縦幅を取得する関数
float VertexManager::GetVtxHeight(int key)
{
	return m_Vertex[key].GetVtxHeight();
}

// バーテックスの奥行を取得する関数
float VertexManager::GetVtxDepth(int key)
{
	return m_Vertex[key].GetVtxDepth();
}

// バーテックスを解放する関数
void VertexManager::Release(int key)
{
	m_Vertex.erase(key);
}

// 全てのバーテックスを解放する関数
void VertexManager::ReleaseALL()
{
	m_Vertex.clear();
}
