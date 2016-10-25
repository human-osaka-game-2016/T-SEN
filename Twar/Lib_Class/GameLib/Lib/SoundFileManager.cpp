/**
* @file SoundFileManager.cpp
* @brief サウンドを管理するクラスのcpp
* @author haga
*/

#include "SoundFileManager.h"

SoundFileManager::SoundFileManager():
m_pDSound8(NULL),
m_releaseFlag(false)
{
}

SoundFileManager::~SoundFileManager()
{
	if (!m_releaseFlag)
	{
		ReleaseALL();
	}
}

void SoundFileManager::InitSound(HWND hWnd)
{
	DirectSoundCreate8(NULL, &m_pDSound8, NULL);
	// 協調レベル設定
	m_pDSound8->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
}

// WAVEファイルオープン関数
bool SoundFileManager::OpenWave(TCHAR* filepath, WAVEFORMATEX* waveFormatEx, char** pwaveData, DWORD* dataSize)
{
	if (filepath == 0)
		return false;

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// waveファイルオープン
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(filepath, &mmioInfo, MMIO_READ);
	if (!hMmio)
		return false; // ファイルオープン失敗

	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}

	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)waveFormatEx, fmsize);
	if (size != fmsize) {
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	*pwaveData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*pwaveData, dataChunk.cksize);
	if (size != dataChunk.cksize) {
		delete[] * pwaveData;
		return false;
	}
	*dataSize = size;

	// ハンドルクローズ
	mmioClose(hMmio, 0);

	return true;
}

HRESULT SoundFileManager::LoadSound(int key,TCHAR* filePath)
{
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	// Waveファイルオープン
	WAVEFORMATEX wFmt;
	char *pWaveData = 0;
	DWORD waveSize = 0;

	if (!OpenWave((filePath), &wFmt, &pWaveData, &waveSize))
	{
		return E_FAIL;
	}

	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = 0;
	DSBufferDesc.dwBufferBytes = waveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &wFmt;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer *ptmpBuf = 0;
	m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &ptmpBuf, NULL);
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pDSBuffer);

	ptmpBuf->Release();
	if (pDSBuffer == NULL)
	{
		m_pDSound8->Release();
		return E_FAIL;
	}


	// セカンダリバッファにWaveデータ書き込み
	//音声データ
	LPVOID lpvWrite = 0;
	//音声データの大きさ
	DWORD dwLength = 0;
	if (DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}

	delete[] pWaveData; // 元音はもういらない


	m_soundMap[key] = pDSBuffer;

	return S_OK;
}

// 音楽を再生する関数
void SoundFileManager::SoundPlayer(int key, SOUND_MODE sMode)
{
	switch (sMode)
	{
	case Play:
		m_soundMap[key]->Play(0, 0, 0);
		break;
	case PlayLoop:
		m_soundMap[key]->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case Stop:
		m_soundMap[key]->Stop();
		break;
	case Reset:
		m_soundMap[key]->SetCurrentPosition(0);
		break;
	case Stop_Reset:
		m_soundMap[key]->Stop();
		m_soundMap[key]->SetCurrentPosition(0);
		break;
	case Reset_Play:
		m_soundMap[key]->SetCurrentPosition(0);
		m_soundMap[key]->Play(0, 0, 0);
		break;

	}
}

// サウンド解放関数
void SoundFileManager::Release(int key)
{
	m_soundMap[key]->Release();
	m_soundMap.erase(key);
}

// 解放関数
void SoundFileManager::ReleaseALL()
{
	for (auto itr = m_soundMap.begin(); itr != m_soundMap.end(); ++itr)
	{
		if (itr->second)
		{
			itr->second->Release();
			itr->second = NULL;
		}
	}

	m_soundMap.clear();

	if (m_pDSound8)
	{
		m_pDSound8->Release();
		m_pDSound8 = NULL;
	}

	m_releaseFlag = true;
}