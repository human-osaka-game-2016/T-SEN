/**
* @file   InputDevice.h
* @brief  DirectInput関連クラスのh
* @author haga
*/
#ifndef INPUT_DEVICE_H
#define	INPUT_DEVICE_H

#include <dinput.h>
/*
* DirectInput関連クラス.
*/

/**ボタンの状態確認*/
enum BTN_STATE
{
	BTN_OFF,		//!< キーを離した状態が続いている
	BTN_ON,			//!< キーを押した状態が続いている
	BTN_PUSH,		//!< キーを押す
	BTN_RELEASE,	//!< キーを離す
};

class InputDevice
{
private:
	HWND				 m_hWnd;			//!< ウィンドウハンドル格納
	LPDIRECTINPUT8		 m_pDInput;			//!< DirectInput
	LPDIRECTINPUTDEVICE8 m_pKeyDevice;		//!< キーボードデバイス
	LPDIRECTINPUTDEVICE8 m_pMouseDevice;	//!< マウスデバイス

public:
	/**コンストラクタ*/
	InputDevice();

	/**デストラクタ*/
	~InputDevice();

	/**
	* デバイスの実体を取得する関数.
	* Singletonパターン<br>
	* @return InputDevice デバイス
	*/
	static InputDevice& GetInstance()
	{
		static InputDevice InputDevice;
		return InputDevice;
	}

	/**
	* DirectInput生成.
	* @retval S_OK		初期化成功
	* @retval E_FAIL	初期化失敗
	*/
	HRESULT InitDinput();

	/**
	* キーボードデバイスの初期化.
	* @param[in] hWnd ウィンドウハンドル
	* @retval S_OK		初期化成功
	* @retval E_FAIL	初期化失敗
	*/
	HRESULT InitDinputKey(HWND hWnd);

	/**
	* マウスデバイスの初期化
	* @param[in] hWnd ウィンドウハンドル
	*/
	HRESULT InitDinputMouse(HWND hWnd);

	/**
	* キーボードデバイス渡す.
	* @return m_pKeyDevice キーボードデバイス
	*/
	LPDIRECTINPUTDEVICE8 GetKeyDevice(){ return m_pKeyDevice; };

	/**
	* マウスデバイス渡す.
	* @return m_pMouseDevice キーボードデバイス
	*/
	LPDIRECTINPUTDEVICE8 GetMouseDevice(){ return m_pMouseDevice; };

	/**
	* 現在使っているウィンドウハンドルを渡す.
	* @return m_hWnd ウィンドウハンドル
	*/
	HWND GethWnd(){ return m_hWnd; };
};

#endif		// INPUT_DEVICE_H