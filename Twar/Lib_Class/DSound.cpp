/**
* @file DSound.cpp
* @brief DirectSoundに関するクラスのcpp
* @author haga
*/
#include <dSound.h>
#include "DSound.h"

// コンストラクタ
DSound::DSound() :m_pDSound8(NULL)
{
}

// デストラクタ
DSound::~DSound()
{
	if (m_pDSound8)
	{
		m_pDSound8->Release();
		m_pDSound8 = NULL;
	}
}

// インターフェイスの初期化
void DSound::InitDSound(HWND hWnd)
{
	DirectSoundCreate8(NULL, &m_pDSound8,NULL);
	// 協調レベル設定
	m_pDSound8->SetCooperativeLevel(hWnd, DSSCL_NORMAL);

}
