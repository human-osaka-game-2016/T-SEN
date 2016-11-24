/**
* @file		LoadingThread.h
* @brief	LoadingThreadクラスヘッダ
* @author	haga
*/
#ifndef LOADING_THREAD_H
#define LOADING_THREAD_H

#include <d3dx9.h>
#include <thread>
#include "GameLib/Lib/Vertex.h"

/**
* ロード画面を管理するクラス.
*/
class LoadingThread
{
public:
	/**
	* スレッドを作成する関数.
	* @param texID	ロード画面で使用するテクスチャーのID
	* @param vtxID	ロード画面で使用するテクスチャーのID
	*/
	static void CreateThread(int texID,int vtxID);

	/**スレッドを破棄する関数*/
	static void DiscardThread();

private:
	static std::thread*			m_pThread;					//!< threadクラスのインスタンスへのポインタ
	static int					m_TexID;					//!< ロード画面に使用するテクスチャーのID
	static int					m_VtxID;					//!< ロード画面に使用するバーテックスのID
	static bool					m_IsLoading;				//!< ロード中かどうかのフラグ

	/**ループ関数(スレッドの実体)*/
	static void LoopLoadingScreen();

	/**コントロール関数*/
	static void Control();

	/**描画関数*/
	static void Draw();

	/**
	* コンストラクタ<br>
	* モノステイトパターンの為private
	*/
	LoadingThread();

};

#endif	// LOADING_THREAD_H
