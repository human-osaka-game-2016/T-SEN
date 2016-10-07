/**
* @file DSound.h
* @brief DirectSoundに関するクラスのh 
* @author haga
*/
#ifndef DSOUND_H
#define DSOUND_H

#include <dSound.h>

/**
* DirectSoundのインターフェイスを作成、取得するクラス.
*/
class DSound
{
private:
	IDirectSound8 *m_pDSound8;		//!< DirectSoundのインターフェイス

public:
	/**コンストラクタ*/
	DSound();

	/**デストラクタ*/
	~DSound();

	/**
	* DirectSoundの実体を取得する関数<br>
	* Singletonパターン.
	* @return IDirectSound8 インターフェイス
	*/
	static DSound& GetInstance()
	{
		static DSound IDirectSound8;

		return IDirectSound8;
	}

	/**
	* インターフェイスを初期化.
	* @param[in] hWnd ウィンドウハンドル
	*/
	void InitDSound(HWND hWnd);

	/**
	* インターフェイスの取得.
	* @return m_pDSound8 インターフェイス
	*/
	IDirectSound8* GetInterface(){ return m_pDSound8; };
};


#endif		// DSOUND_H