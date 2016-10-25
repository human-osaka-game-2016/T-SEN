/**
* @file VertexManager.cpp
* @brief Vertexクラスを管理するクラス
* @author haga
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
	float tuMax, float tvMax, float tuMin, float tvMin)
{
	Vertex vtx(width,height,depth,tuMax,tvMax,tuMin,tvMin);

	m_vertex[key] = vtx;
}

// XY軸で描画する関数
void VertexManager::Draw(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y)
{
	m_vertex[key].Draw(pTexture,x,y);
}

// XZ軸で描画する関数
void VertexManager::Draw(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y, float z)
{
	m_vertex[key].Draw(pTexture, x, y,z);
}

// XY軸でバーテックスの中心座標で描画する関数
void VertexManager::DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y)
{
	m_vertex[key].DrawCenterPos(pTexture, x, y);
}

// XZ軸でバーテックスの中心座標で描画する関数
void VertexManager::DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y, float z)
{
	m_vertex[key].DrawCenterPos(pTexture, x, y,z);
}

// サイズを変更する関数
void VertexManager::SetSize(int key, float width, float height, float depth)
{
	m_vertex[key].SetTexSize(width,height);
}

// tu値とtv値を変更する関数
void VertexManager::SetTuTv(int key, float tuMin, float tuMax, float tvMin, float tvMax)
{
	m_vertex[key].SetTuTvVal(tuMin,tuMax,tvMin,tvMax);
}

// 色を変更する関数
void VertexManager::SetColor(int key, DWORD color)
{
	m_vertex[key].SetColor(color);
}

// バーテックスを解放する関数
void VertexManager::Release(int key)
{
	m_vertex.erase(key);
}

// 全てのバーテックスを解放する関数
void VertexManager::ReleaseALL()
{
	m_vertex.clear();
}
