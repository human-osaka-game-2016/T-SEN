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


void VertexManager::CreateVertex(int key, float width, float height, float depth,
	float tuMax, float tvMax, float tuMin, float tvMin)
{
	Vertex vtx(width,height,depth,tuMax,tvMax,tuMin,tvMin);

	m_vertex[key] = vtx;
}

void VertexManager::Draw(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y)
{
	m_vertex[key].Draw(pTexture,x,y);
}

void VertexManager::Draw(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y, float z)
{
	m_vertex[key].Draw(pTexture, x, y,z);
}

void VertexManager::DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y)
{
	m_vertex[key].DrawCenterPos(pTexture, x, y);
}

void VertexManager::DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y, float z)
{
	m_vertex[key].DrawCenterPos(pTexture, x, y,z);
}

void VertexManager::SetSize(int key, float width, float height, float depth)
{
	m_vertex[key].SetTexSize(width,height);
}

void VertexManager::SetTuTv(int key, float tuMin, float tuMax, float tvMin, float tvMax)
{
	m_vertex[key].SetTuTvVal(tuMin,tuMax,tvMin,tvMax);
}

void VertexManager::SetColor(int key, DWORD color)
{
	m_vertex[key].SetColor(color);
}

void VertexManager::Release(int key)
{
	m_vertex.erase(key);
}

void VertexManager::ReleaseALL()
{
	m_vertex.clear();
}
