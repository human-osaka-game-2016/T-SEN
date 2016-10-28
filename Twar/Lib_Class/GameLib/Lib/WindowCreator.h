/**
* @file WindowCreator.h
* @brief ウィンドウを作成するクラス
* @author haga
* @data 2016/09/28
*/
#ifndef WINDOW_CREATOR_H
#define WINDOW_CREATOR_H
#include <windows.h>
/*
*ウィンドウを作成するクラス
*/
class WindowCreator
{
private:

	WNDCLASSEX  m_wndc;				//!< ウィンドウクラス
	HWND		m_hWnd;				//!< ウィンドウハンドル
	RECT		m_wRect;			//!< ウインドウサイズを保持しておく変数
	TCHAR*      m_wTitle;			//!< ウィンドウのタイトル
	int		    m_wWidth;			//!< ウインドウの幅
	int			m_wHeight;			//!< ウィンドウの高さ
	bool		m_wType;			//!< ウィンドウサイズが通常ならtrue,フルスクリーンならfalse

public:
	/**
	* コンストラクタ.
	* @param[in] title	ウィンドウのタイトル
	* @param[in] width	ウインドウのクライアントサイズ(幅)
	* @param[in] height	ウインドウのクライアントサイズ(高さ)
	*/
	WindowCreator(TCHAR*  title, int width, int height);

	/**デストラクタ*/
	~WindowCreator();

	/**
	* ウィンドウを作成する関数<br>
	* @param[in] hInstance	インスタンスハンドル
	* @param[in] Wndproc	ウィンドウプロシージャ関数
	* @param[in] windowType ウィンドウタイプ trueなら通常,falseならフルスクリーン
	* @retval S_OK			ウィンドウ生成に成功した
	* @retval E_FAIL		ウィンドウ生成に失敗した
	*/
	HRESULT MakeWindow(HINSTANCE hInstance, LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp), bool windowType);

	/**
	* ウィンドウサイズ変更
	*/
	HRESULT ChangeWindowSize();

	/**
	* ハンドル取得用関数.
	* @return m_hWnd ウィンドウハンドル
	*/
	HWND GetHwnd(){ return m_hWnd; };

};

#endif	// WINDOW_CREATOR_H