//==================================================================================================================================//
//!< @file		WindowCreator.h
//!< @brief		WindowCreatorクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef WINDOW_CREATOR_H
#define WINDOW_CREATOR_H

#include <windows.h>

/**ウィンドウを作成するクラス*/
class WindowCreator
{

public:
	/**
	* Constructor.
	* @param[in] pTitle	ウィンドウのタイトル
	* @param[in] width	ウインドウのクライアントサイズ(幅)
	* @param[in] height	ウインドウのクライアントサイズ(高さ)
	*/
	WindowCreator(TCHAR*  pTitle, int width, int height);

	/**Destructor*/
	~WindowCreator();

	/**
	* ウィンドウを作成する関数<br>
	* @param[in] hInstance		インスタンスハンドル
	* @param[in] Wndproc		ウィンドウプロシージャ関数
	* @param[in] isFullScreen	ウィンドウタイプ trueならフルスクリーン,falseなら通常画面
	* @retval S_OK				ウィンドウ生成に成功した
	* @retval E_FAIL			ウィンドウ生成に失敗した
	*/
	HRESULT MakeWindow(HINSTANCE hInstance, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM), bool isFullScreen);

	/**ウィンドウサイズ変更*/
	HRESULT ChangeWindowSize();

	/**
	* ハンドル取得用関数.
	* @return m_hWnd ウィンドウハンドル
	*/
	inline HWND GetHwnd(){ return m_hWnd; };

private:
	WNDCLASSEX  m_Wndc;					//!< ウィンドウクラス
	HWND		m_hWnd;					//!< ウィンドウハンドル
	RECT		m_wRect;				//!< ウインドウサイズを保持しておく変数
	TCHAR*      m_pWinTitle;			//!< ウィンドウのタイトル
	int		    m_WinWidth;				//!< ウインドウの幅
	int			m_WinHeight;			//!< ウィンドウの高さ
	bool		m_IsFullScreen;			//!< ウィンドウタイプ trueならフルスクリーン falseなら通常

};

#endif	// WINDOW_CREATOR_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
