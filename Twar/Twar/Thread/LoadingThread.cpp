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
}

//-----------------------------------------------------------------------------------------------------//
//Static private functions
//-----------------------------------------------------------------------------------------------------//

// ループ関数(スレッドの実体)
void LoadingThread::LoopLoadingScreen()
{
	CUSTOMVERTEX loadingScreen[] =
	{
		{	 0,	  0, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
		{ 1600,   0, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
		{ 1600, 900, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
		{	 0, 900, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
	};

	DWORD currentTime;					// 現在の時間
	DWORD oldTime = timeGetTime();		// 前の時間

	while (m_IsLoading)
	{
		currentTime = timeGetTime();				
		if(currentTime - oldTime >= ( 1000 / 60 ))
		{
			Control(loadingScreen, sizeof(loadingScreen) / sizeof(CUSTOMVERTEX));
			Draw(loadingScreen);
			oldTime = currentTime;
		}
	}
}

// コントロール関数
void LoadingThread::Control(CUSTOMVERTEX vtx[], int vtxNum)
{
	for(int i = 0; i < vtxNum; i++)
	{
		vtx[i].tu += 0.005f;
	}
}

// 描画関数
void LoadingThread::Draw(CUSTOMVERTEX vtx[])
{
	GameLib::Instance().StartRender();
	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtx, sizeof(CUSTOMVERTEX));
	GameLib::Instance().EndRender();
}

//-------------------------------------------------------------------------------------------------//
//Private functions
//-------------------------------------------------------------------------------------------------//

LoadingThread::LoadingThread()
{
}

