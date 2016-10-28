/**
* @file	XFileManager.cpp
* @brief Xファイルを管理するクラス
* @author haga
*/
#include "XFile.h"
#include "XFileManager.h"


XFileManager::XFileManager()
{
}


XFileManager::~XFileManager()
{
	ReleaseALL();
}

// Xファイルを読み込む関数
void XFileManager::Load(int key, LPCTSTR pFilePath)
{
	XFile xFile;
	m_xFile[key] = xFile;
	m_xFile[key].LoadXFile(pFilePath);

}

// Xファイルを描画する関数
void XFileManager::Draw(int key)
{
	m_xFile[key].DrawX();
}

// 解放関数
void XFileManager::Release(int key)
{
	m_xFile[key].Release();
	m_xFile.erase(key);
}

// 管理しているファイルをすべて解放する関数
void XFileManager::ReleaseALL()
{
	m_xFile.clear();
}