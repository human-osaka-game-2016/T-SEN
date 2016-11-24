/**
* @file		LoadingThread.cpp
* @brief	LoadingThreadクラス実装
* @author	haga
*/

//-------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------//
#include "GameLib/GameLib.h"
#include "LoadingThread.h"

//-------------------------------------------------------------------------------------------------//
//Static private variables
//-------------------------------------------------------------------------------------------------//
std::thread*	LoadingThread::m_pThread = nullptr;
bool			LoadingThread::m_IsLoading = false;
int				LoadingThread::m_TexID = INT_MAX;			// 登録されないだろう数値を代入している
int				LoadingThread::m_VtxID = INT_MAX;			// 登録されないだろう数値を代入している

//-----------------------------------------------------------------------------------------------------//
//Static public functions
//-----------------------------------------------------------------------------------------------------//

//	スレッドを作成する関数
void LoadingThread::CreateThread(int texID,int vtxID)
{
	if(m_pThread != nullptr)			// スレッドがあるかどうかチェック
	{
		MessageBox(0, "スレッドがすでに作成されています。", NULL, MB_OK);
		return;
	}

	m_TexID = texID;
	m_VtxID = vtxID;
	m_IsLoading = true;
	m_pThread = new std::thread(LoopLoadingScreen);
}

// スレッドを破棄する関数
void LoadingThread::DiscardThread()
{
	if(m_pThread == nullptr)		// スレッドがあるかどうかチェック
	{
		MessageBox(0, "このスレッドはありません。", NULL, MB_OK);
		return;
	}

	m_IsLoading = false;

	m_pThread->join();				// スレッドが終了するまで待機する

	delete m_pThread;
	m_pThread = nullptr;
	m_TexID = INT_MAX;				// 登録されないだろう数値を代入している
	m_VtxID = INT_MAX;				// 登録されないだろう数値を代入している
}

//-----------------------------------------------------------------------------------------------------//
//Static private functions
//-----------------------------------------------------------------------------------------------------//

// ループ関数(スレッドの実体)
void LoadingThread::LoopLoadingScreen()
{
	DWORD currentTime;					// 現在の時間
	DWORD oldTime = timeGetTime();		// 前の時間

	while (m_IsLoading)
	{
		currentTime = timeGetTime();				
		if(currentTime - oldTime >= ( 1000 / 60 ))
		{
			Control();
			Draw();
			oldTime = currentTime;
		}
	}
}

// コントロール関数
void LoadingThread::Control()
{
	GameLib::Instance().ScrollUV(m_VtxID,0.005f,0.0f);
}

// 描画関数
void LoadingThread::Draw()
{
	GameLib::Instance().StartRender();
	GameLib::Instance().DrawXY(m_TexID,m_VtxID,0.0f,0.0f);
	GameLib::Instance().EndRender();
}

//-------------------------------------------------------------------------------------------------//
//Private functions
//-------------------------------------------------------------------------------------------------//

LoadingThread::LoadingThread()
{
}

