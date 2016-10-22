/**
* @file VertexManager.h
* @brief Vertexクラスを管理するクラス
* @author haga
*/
#ifndef VERTEX_MANAGER_H
#define VERTEX_MANAGER_H

#include <map>
#include "Vertex.h"
using namespace std;

class VertexManager
{
private:
	std::map<int, Vertex> m_vertex;

public:
	VertexManager();
	~VertexManager();

	// バーテックスクラスを作成し、登録する関数
	void CreateVertex(int key,float width, float height, float depth = 0.0f,
		float tuMax = 1.0f, float tvMax = 1.0f, float tuMin = 0.0f, float tvMin = 0.0f);

	void Draw(int key, LPDIRECT3DTEXTURE9 pTexture,float x,float y);

	void Draw(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y, float z);

	void DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture,float x,float y);

	void DrawCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float x, float y,float z);

	void SetSize(int key, float width, float height, float depth = 0.0f);

	void SetTuTv(int key, float tuMin, float tuMax, float tvMin, float tvMax);

	void SetColor(int key, DWORD color);

	void Release(int key);

	void ReleaseALL();
};

#endif	// VERTEX_MANAGER_H