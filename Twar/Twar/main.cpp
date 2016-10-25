/**
* @file main.cpp
* @brief T戦のmain.cppです
* @author haga
*/
#include <windows.h>
#include <crtdbg.h>
#include <d3dx9.h>
#include <dinput.h>
#include "./GameLib/GameLib.h"

//#define FULLSCREEN

#define WINDOW_TITLE TEXT("T戦")		// ウィンドウタイトル
#define CLIENT_SIZE_W 1600				// クライアントサイズの幅
#define CLIENT_SIZE_H 900 				// クライアントサイズの高さ
#define GAME_FPS (1000 / 60)			// ゲームFPS

GameLib*		g_pGameLib = NULL;

// プロシージャ関数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg;

	g_pGameLib = &GameLib::GetInstance();
	//-------------------------------------------------------------------
	//				         ウィンドウ生成
	//-------------------------------------------------------------------	
#ifndef FULLSCREEN

	g_pGameLib->InitGameLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H,hInstance, WindowProc, true);

#else
	g_pGameLib->InitGameLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H,hInstance, WindowProc, false);

#endif

	//-------------------------------------------------------------------
	//						メッセージループ
	//-------------------------------------------------------------------


	DWORD currentTime = timeGetTime();		// 現在の時間
	DWORD oldTime = timeGetTime();			// 前の時間

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			currentTime = timeGetTime();
			if (currentTime - oldTime >= GAME_FPS)
			{
				oldTime = timeGetTime();
			}
		}
	}

	g_pGameLib->ReleaseGameLib();

	return (INT)msg.wParam;
}
// ウインドウプロシージャ関数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		int a = MessageBox(hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO);
		if (a == IDYES)
		{
			PostQuitMessage(0);
			
		}
		return  0;
	}
		
		break;
	case WM_KEYDOWN:
		switch ((CHAR)wparam)
		{
		case VK_ESCAPE:
		{
			int a = MessageBox(hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO);
			if (a == IDYES)
			{
				PostQuitMessage(0);
				return 0;
			}
		}
			
			break;
		}
		break;

	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch ((CHAR)wparam)
		{
		case VK_RETURN:     // Alt + Enterを押すとウィンドウ切り替え
			g_pGameLib->ChangeWindowMode();
			break;
		default:
			break;
		}
		break;

	case WM_ACTIVATE:
		switch ((CHAR)wparam)
		{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:

			break;
		}
	}
	return  DefWindowProc(hwnd, message, wparam, lparam);
}