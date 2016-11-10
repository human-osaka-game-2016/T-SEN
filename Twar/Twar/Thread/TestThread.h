/**
* @file  TestThread.h
* @brief テストスレッド（マルチスレッド）
* @author
*/
#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "GameLib/Lib/Vertex.h"

class TestThread
{
public:

	TestThread();

	~TestThread();

	// スレッド作成関数
	bool CreateTestThread(LPDIRECT3DTEXTURE9 tex);

	// スレット破棄関数
	bool DeleteTestThread();
	
private:
	HANDLE			m_hThread;		// スレッドハンドルを格納する変数
	DWORD			m_threadID;		// スレッドIDを格納する変数
	static bool		m_threadEnd;	// スレッド終了フラグ

	// スレッド関数
	static DWORD WINAPI ThreadFunc(LPVOID tex);

	// コントロール関数
	static void Control(CUSTOMVERTEX* vtx, int vtxNum);

	// 描画関数
	static void Draw(CUSTOMVERTEX* vtx, LPDIRECT3DTEXTURE9 tex);

	
};

#endif // TEST_THREAD_H