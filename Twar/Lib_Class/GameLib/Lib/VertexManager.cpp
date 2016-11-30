/**
* @file		VertexManager.cpp
* @brief	VertexManagerクラス実装
* @author	haga
*/

#include "VertexManager.h"

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

// XY軸で描画する関数
void VertexManager::Draw(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{
	m_Vertex[key].Draw(pTexture, posX, posY);
}

// XZ軸で描画する関数
void VertexManager::Draw(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ)
{
	m_Vertex[key].Draw(pTexture, posX, posY, posZ);
}

// XY軸でバーテックスの中心座標で描画する関数
void VertexManager::DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{
	m_Vertex[key].DrawCenterPos(pTexture, posX, posY);
}

// XZ軸でバーテックスの中心座標で描画する関数
void VertexManager::DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ)
{
	m_Vertex[key].DrawCenterPos(pTexture, posX, posY, posZ);
}

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
