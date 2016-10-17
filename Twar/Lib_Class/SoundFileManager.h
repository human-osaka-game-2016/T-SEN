/**
* @file SoundFileManager
* @brief  サウンドを管理するクラスのh
* @author haga
*/
#ifndef SOUND_FILE_MANAGER_H
#define SOUND_FILE_MANAGER_H

#include <windows.h>
#include <mmsystem.h>
#include <map>
#include <dsound.h>
using namespace std;

//#pragma comment(lib, "dsound.lib")

/**音楽の再生方式*/
enum SOUND_MODE
{
	Play,			//!< 再生
	PlayLoop,		//!< ループ再生
	Stop,			//!< 停止
	Reset,			//!< 初期位置に戻す
	Stop_Reset,		//!< 停めて初期位置戻す
	Reset_Play		//!< 初期位置から再生し直す
};


/**
* サウンドを管理するクラス
*/
class SoundFileManager
{
private:
	IDirectSound8*								m_pDSound8;										//!< DirectSoundのインターフェイス
	std::map<TCHAR*, LPDIRECTSOUNDBUFFER8> m_soundMap;			//!< サウンドファイルを格納する変数

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
	SoundFileManager();
	/**dデストラクタ*/
	~SoundFileManager();

	/**
	* Singltonパターン
	*/
	static SoundFileManager& GetInstance()
	{
		static SoundFileManager soundFileManager;

		return soundFileManager;
	}

	/**
	* DirectSound初期化する関数
	* @param[in] hWnd ウィンドウハンドル
	*/
	void InitSound(HWND hWnd);

	/**
	* 音楽を読み込む関数.
	* @param[in]	filepath	音楽ファイル名
	* @retval S_OK		読み込み成功
	* @retval E_FAIL	読み込み失敗
	*/
	HRESULT LoadSound(TCHAR* filePath);

	/**
	* 音楽を再生する関数
	* @param[in] filePath  ファイル名(mapのキーの役割)
	* @param[in] mode		音楽の再生方式
	*/
	void SoundPlayer(TCHAR* filePath, SOUND_MODE sMode);
};



#endif	// SOUND_FILE_MANAGER_H