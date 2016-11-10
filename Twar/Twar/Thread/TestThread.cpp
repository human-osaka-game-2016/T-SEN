
#include "TestThread.h"

bool TestThread::m_threadEnd;

TestThread::TestThread()
	: m_hThread(nullptr)
	, m_threadID(0)
{
	m_threadEnd = false;
}


TestThread::~TestThread()
{
	if (m_hThread != nullptr)
	{
		CloseHandle(m_hThread);
	}
}

// スレッド作成関数
bool TestThread::CreateTestThread(LPDIRECT3DTEXTURE9 tex)
{
	// スレッドがすでにあったら処理を終了する
	if (m_hThread != nullptr)
	{
		return false;
	}

	// スレッドを作成する
	m_hThread = CreateThread(NULL, 0, this->ThreadFunc, (LPVOID)tex, 0, &m_threadID);

	if (m_hThread == nullptr)
	{
		return false;
	}
	return true;
}

bool TestThread::DeleteTestThread()
{
	// スレッドがないなら処理を終了する
	if (m_hThread == nullptr)
	{
		return false;
	}

	// スレッドの終了フラグをたてる
	m_threadEnd = true;

	// スレッドが終了するまで待機
	WaitForSingleObject(m_hThread, INFINITE);

	// スレッドを解除する
	CloseHandle(m_hThread);

	// 初期状態にする
	m_hThread = nullptr;
	m_threadID = 0;
	m_threadEnd = false;

	return true;
}

// スレッド関数
DWORD WINAPI TestThread::ThreadFunc(LPVOID tex)
{
	CUSTOMVERTEX threadBG[] =
	{
		{	 0,	400, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
		{ 1600, 400, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
		{ 1600, 500, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
		{	 0, 500, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
	};

	LPDIRECT3DTEXTURE9 threadTex = reinterpret_cast<LPDIRECT3DTEXTURE9>(tex);

	DWORD currentTime = timeGetTime();		// 現在の時間
	DWORD oldTime = timeGetTime();			// 前の時間

	while (!m_threadEnd)
	{
		currentTime = timeGetTime();
		if (currentTime - oldTime >= (1000 / 60))
		{
			Control(threadBG,4);
			Draw(threadBG, threadTex);
			oldTime = currentTime;
		}
	}
	return (DWORD)0;
}

// コントロール関数
void TestThread::Control(CUSTOMVERTEX* vtx,int vtxNum)
{
	for (int i = 0; i < vtxNum;i++)
	{
		vtx[i].tu += 0.005f;
	}
}

// 描画関数
void TestThread::Draw(CUSTOMVERTEX* vtx, LPDIRECT3DTEXTURE9 tex)
{
	GraphicsDevice::GetInstance().StartRender(D3DFVF_CUSTOMVERTEX);

	GraphicsDevice::GetInstance().GetDevice()->SetTexture(0, tex);
	GraphicsDevice::GetInstance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtx, sizeof(CUSTOMVERTEX));

	GraphicsDevice::GetInstance().EndRender();
}