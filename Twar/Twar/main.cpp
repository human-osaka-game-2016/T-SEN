/**
* @file main.cpp
* @brief T戦のmain.cppです
* @author haga
*/
#include <windows.h>
#include <crtdbg.h>
#include <d3dx9.h>
#include <dinput.h>
#include "WindowCreator.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "SoundFileManager.h"
#include "Font.h"


//#define FULLSCREEN

#define WINDOW_TITLE TEXT("T戦")		// ウィンドウタイトル
#define CLIENT_SIZE_W 1600				// クライアントサイズの幅
#define CLIENT_SIZE_H 900 				// クライアントサイズの高さ
#define GAME_FPS (1000 / 60)			// ゲームFPS


WindowCreator*  g_pGameWindow = NULL;
GraphicsDevice* g_pGraphicsDevice = NULL;				// DirectXDevice
InputDevice*	g_pInputDevice = NULL;					// DirectInput

// プロシージャ関数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg;

	//-------------------------------------------------------------------
	//				         ウィンドウ生成
	//-------------------------------------------------------------------	
	g_pGameWindow = new WindowCreator(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H);
#ifndef FULLSCREEN

	g_pGameWindow->MakeWindow(hInstance, WindowProc, true);

#else

	g_pGameWindow->MakeWindow(hInstance, WindowProc, false);

#endif

	//-------------------------------------------------------------------
	//						  DirectX関連
	//-------------------------------------------------------------------

	// グラフィックデバイス
	g_pGraphicsDevice = &GraphicsDevice::GetInstance();
#ifndef FULLSCREEN

	g_pGraphicsDevice->InitDevice(g_pGameWindow->GetHwnd(), true, CLIENT_SIZE_W, CLIENT_SIZE_H);

#else

	pGraphicsDevice->InitDevice(g_pGameWindow->GetHwnd(), false, CLIENT_SIZE_W, CLIENT_SIZE_H);

#endif


	g_pGraphicsDevice->SetRenderState3D();

	// ダイレクトインプット
	g_pInputDevice = &InputDevice::GetInstance();
	g_pInputDevice->InitDinput();
	g_pInputDevice->InitDinputKey(g_pGameWindow->GetHwnd());
	g_pInputDevice->InitDinputMouse(g_pGameWindow->GetHwnd());

	// ダイレクトサウンド
	SoundFileManager* pSoundFileManager = NULL;
	pSoundFileManager = &SoundFileManager::GetInstance();
	pSoundFileManager->InitSound(g_pGameWindow->GetHwnd());

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


	delete g_pGameWindow;

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
	}
		return  0;
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
			}
		}
			return 0;
			break;
		}
		break;

	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch ((CHAR)wparam)
		{
		case VK_RETURN:     // Alt + Enterを押すとウィンドウ切り替え
			g_pGraphicsDevice->ChangeDisplayMode();
			g_pGameWindow->ChangeWindowSize();
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