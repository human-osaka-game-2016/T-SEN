/**
* @file TextureManager.h
* @brief テクスチャーを管理するクラスのh
* @author haga
*/
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <d3dx9.h>
#include <d3d9.h>
#include "GraphicsDevice.h"
#include <map>
using namespace std;

class TextureManager
{
private:
	IDirect3DDevice9*				  m_pD3Device;	//!< デバイス
	std::map<int, LPDIRECT3DTEXTURE9> m_texture;

public:
	TextureManager();
	~TextureManager();
	void Load(int key,char* filePath); 
	void LoadEx(int key, char* filePath, int a = 255, int r = 0, int g = 0, int b = 0, bool size = false);
	LPDIRECT3DTEXTURE9 GetTex(int key);
	void Release(int key);
	void ReleaseALL();

};

#endif	// TEXTURE_MANAGER_H
