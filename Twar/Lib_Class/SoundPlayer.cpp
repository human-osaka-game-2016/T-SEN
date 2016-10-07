/**
* @file  SoundPlayer.cpp
* @brief 音楽の再生に関するクラス.cpp
* @author haga
*/
#include <windows.h>
#include <dSound.h>
#include "Dsound.h"
#include "SoundPlayer.h"

// コンストラクタ
SoundPlayer::SoundPlayer() :m_pDSound8(DSound::GetInstance().GetInterface()), m_pDSBuffer(NULL)
{
}
// デストラクタ
SoundPlayer::~SoundPlayer()
{
	if (m_pDSBuffer)
	{
		m_pDSBuffer->Release();
		m_pDSBuffer = NULL;
	}
}

// WAVEファイルオープン関数
bool SoundPlayer::OpenWave(TCHAR* filepath, WAVEFORMATEX* waveFormatEx, char** pwaveData, DWORD* dataSize)
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

// 音楽を読み込む
HRESULT SoundPlayer::LoadSound(TCHAR* filepath)
{
	WAVEFORMATEX wFmt; 
	char *pWaveData = 0; 
	DWORD dataSize = 0; 

	if (!OpenWave(filepath, &wFmt, &pWaveData, &dataSize))
	{
		MessageBox(0, "WAVEファイルオープンに失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}

	// セカンダリバッファ作成
	DSBUFFERDESC DSBufferDesc;

	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = 0;
	DSBufferDesc.dwBufferBytes = dataSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &wFmt;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;


	IDirectSoundBuffer *ptmpBuf = 0;
	m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &ptmpBuf, NULL);
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_pDSBuffer);
	ptmpBuf->Release();

	// セカンダリバッファにWaveデータ書き込み
	LPVOID lpvWrite = 0;
	DWORD dwLength = 0;
	if (DS_OK == m_pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER)) 
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		m_pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}
	else
	{
		MessageBox(0, "WAVEファイルバッファ書き込みに失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}

	delete[] pWaveData;

	return S_OK;
}

// 音楽再生モード
void SoundPlayer::SoundMode(SOUNDMODE _sMode)
{
	switch (_sMode)
	{
	case Play:
		m_pDSBuffer->Play(0, 0, 0);
		break;
	case PlayLoop:
		m_pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case Stop:
		m_pDSBuffer->Stop();
		break;
	case Reset:
		m_pDSBuffer->SetCurrentPosition(0);
		break;
	case Stop_Reset:
		m_pDSBuffer->Stop();
		m_pDSBuffer->SetCurrentPosition(0);
		break;
	case Reset_Play:
		m_pDSBuffer->SetCurrentPosition(0);
		m_pDSBuffer->Play(0, 0, 0);
		break;

	}
}