//==================================================================================================================================//
//!< @file		WindowCreator.cpp
//!< @brief		WindowCreatorクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <windows.h>
#include "WindowCreator.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

WindowCreator::WindowCreator(TCHAR*  pTitle, int width, int height) 
	: m_hWnd(NULL)
	, m_pWinTitle(pTitle)
	, m_WinWidth(width)
	, m_WinHeight(height)
	, m_IsFullScreen(false)
{}

WindowCreator::~WindowCreator()
{}

// ウィンドウを作成する関数
HRESULT WindowCreator::MakeWindow(HINSTANCE hInstance, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM), bool isFullScreen)
{
	// ウィンドウ情報の設定
	m_Wndc.cbSize			= sizeof(m_Wndc);
	m_Wndc.style			= CS_HREDRAW | CS_VREDRAW;
	m_Wndc.lpfnWndProc		= WndProc;
	m_Wndc.cbClsExtra		= m_Wndc.cbWndExtra = 0;
	m_Wndc.hInstance		= hInstance;
	m_Wndc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	m_Wndc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	m_Wndc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_Wndc.lpszMenuName		= NULL;
	m_Wndc.lpszClassName	= m_pWinTitle;
	m_Wndc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_Wndc))
	{
		MessageBox(0, "ウィンドウクラスの設定に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}
	else
	{
		// ウィンドウクラスの設定成功。 チェック用空処理
	}

	m_IsFullScreen = isFullScreen;  // ウィンドウタイプを保持する

	// ウィンドウを作る	
	if(m_IsFullScreen)			// フルスクリーン
	{
		m_hWnd = CreateWindow(
			m_pWinTitle,							// ウィンドウのクラス名
			m_pWinTitle, 							// ウィンドウのタイトル
			WS_POPUP | WS_VISIBLE,					// ウィンドウスタイル
			0,										// ウィンドウの横方向の位置x
			0,										// ウィンドウの縦方向の位置y
			m_WinWidth,								// Width（幅）　
			m_WinHeight,							// Height（高さ)
			NULL,
			NULL,
			hInstance,								// アプリケーションインスタンスのハンドル
			NULL
			);
	}
	else						// 通常ウィンドウ
	{
		m_hWnd = CreateWindow(
			m_pWinTitle,							// ウィンドウのクラス名
			m_pWinTitle, 							// ウィンドウのタイトル
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,		// ウィンドウスタイル
			CW_USEDEFAULT,							// ウィンドウの横方向の位置x
			CW_USEDEFAULT,							// ウィンドウの縦方向の位置y
			m_WinWidth,								// Width（幅）　
			m_WinHeight,							// Height（高さ)
			NULL,
			NULL,
			hInstance,								// アプリケーションインスタンスのハンドル
			NULL
			);

		SetProcessDPIAware();						// ウィンドウサイズを調整する関数
		HDC hdc = GetDC(m_hWnd);
		int aaa = GetDeviceCaps(hdc, LOGPIXELSX);

		// クライアント領域を調整する
		RECT client_rect;
		RECT widow_rect;
		GetWindowRect(m_hWnd, &widow_rect);
		GetClientRect(m_hWnd, &client_rect);

		// 正しいウィンドウ間隔を求める(幅)
		widow_rect.right	-= widow_rect.left;
		client_rect.right	-= client_rect.left;

		// 正しいウィンドウ間隔を求める(高さ)
		widow_rect.bottom	-= widow_rect.top;
		client_rect.bottom	-= client_rect.top;

		// ウィンドウサイズを調整する
		SetWindowPos(m_hWnd, HWND_TOP, 0, 0, (m_WinWidth + (widow_rect.right - client_rect.right)), (m_WinHeight + (widow_rect.bottom - client_rect.bottom)), SWP_NOMOVE);
		GetWindowRect(m_hWnd, &m_wRect);		// ウィンドウサイズを保持しておく
	}

	if (!m_hWnd)
	{
		MessageBox(0, "ウィンドウ生成に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}
	else
	{
		// ウィンドウ生成成功 チェック用空処理
	}

	ShowWindow(m_hWnd, SW_SHOW);

	return S_OK;
}


// ウィンドウサイズを変更する
HRESULT WindowCreator::ChangeWindowSize()
{
	if(m_IsFullScreen)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		SetWindowPos(m_hWnd, HWND_TOP, 0, 0, m_WinWidth, m_WinHeight, SWP_NOMOVE);

		// クライアント領域を調整する
		RECT client_rect;
		RECT widow_rect;
		GetWindowRect(m_hWnd, &widow_rect);
		GetClientRect(m_hWnd, &client_rect);

		// 正しいウィンドウ間隔を求める(幅)
		widow_rect.right	-= widow_rect.left;
		client_rect.right	-= client_rect.left;

		// 正しいウィンドウ間隔を求める(高さ)
		widow_rect.bottom	-= widow_rect.top;
		client_rect.bottom	-= client_rect.top;

		SetWindowPos(m_hWnd, HWND_TOP, 0, 0, (m_WinWidth + (widow_rect.right - client_rect.right)), (m_WinHeight + (widow_rect.bottom - client_rect.bottom)), SWP_NOMOVE);
		GetWindowRect(m_hWnd, &m_wRect);

		m_IsFullScreen = false;
	}
	else
	{
		SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		m_IsFullScreen = false;
	}

	return S_OK;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
