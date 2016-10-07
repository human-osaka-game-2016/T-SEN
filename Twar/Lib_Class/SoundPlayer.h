/**
* @file  SoundPlayer.h
* @brief 音楽の再生に関するクラス.h
* @author haga
*/
#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <windows.h>
#include <dSound.h>
#include "Dsound.h"

/**音楽の再生形式*/
enum SOUNDMODE
{
	Play,			//!< 再生
	PlayLoop,		//!< ループ再生
	Stop,			//!< 停止
	Reset,			//!< 初期位置に戻す
	Stop_Reset,		//!< 停めて初期位置戻す
	Reset_Play		//!< 初期位置から再生し直す
};

/**
* 音楽を管理するクラス.
*/
class SoundPlayer
{
private:
	IDirectSound8 *m_pDSound8;			//!< DirectSoundのインターフェイス
	IDirectSoundBuffer8 *m_pDSBuffer;   //!< 曲を格納するバッファ

	/**
	* WAVEファイルオープン関数.
	* @param[in]	filepath		音楽ファイル名
	* @param[out]   waveFormatEx	waveフォーマット
	* @param[out]	pwaveData		waveデータ
	* @param[out]	dataSize		データサイズ
	* @retval	true	waveファイルオープン成功
	* @retval	false	waveファイルオープン失敗
	*/
	bool OpenWave(TCHAR* filepath, WAVEFORMATEX* waveFormatEx, char** pwaveData, DWORD* dataSize);

public:
	/**コンストラクタ*/
	SoundPlayer();

	/**デストラクタ*/
	~SoundPlayer();

	/**
	* 音楽を読み込む関数.
	* @param[in]	filepath	音楽ファイル名
	* @retval S_OK		読み込み成功
	* @retval E_FAIL	読み込み失敗
	*/
	HRESULT LoadSound(TCHAR* filepath);

	/**
	* 音楽再生モード.
	* @param[in] sMode 音楽操作方法
	*/
	void SoundMode(SOUNDMODE sMode);

};

#endif		// SOUND_PLAYER_H