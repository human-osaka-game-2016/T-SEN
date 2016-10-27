/**
* @file   InputDevice.cpp
* @brief  DirectInput関連クラスのcpp
* @author haga
*/
#include <dinput.h>
#include "InputDevice.h"

// コンストラクタ
InputDevice::InputDevice() : m_pDInput(NULL),
m_pKeyDevice(NULL),
m_pMouseDevice(NULL),
m_hWnd(NULL)
{
}

// デストラクタ(ここでデバイスなどを開放している)
InputDevice::~InputDevice()
{
	if (m_pKeyDevice)
	{
		m_pKeyDevice->Release();
		m_pKeyDevice = NULL;
	}

	if (m_pMouseDevice)
	{
		m_pMouseDevice->Release();
		m_pMouseDevice = NULL;
	}
	
	if (m_pDInput)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

// DirectInput生成
HRESULT InputDevice::InitDinput()
{
	//	DirectInput オブジェクトの作成
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDInput, NULL)))
	{
		MessageBox(0, "DirectInputオブジェクト生成に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

// キーボードデバイス初期化
HRESULT InputDevice::InitDinputKey(HWND hWnd)
{
	// メンバーにハンドルを格納する
	m_hWnd = hWnd;

	//	キーボードの初期化
	if (FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice, NULL)))
	{
		MessageBox(0, "DirectInputキーボード初期化に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}

	//	データフォーマット
	if (FAILED(m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//	協調レベル
	if (FAILED(m_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	// アクセス許可
	m_pKeyDevice->Acquire();
	return S_OK;
}

// マウスデバイス初期化
HRESULT InputDevice::InitDinputMouse(HWND hWnd)
{
	//	キーボードの初期化
	if (FAILED(m_pDInput->CreateDevice(GUID_SysMouse,
		&m_pMouseDevice, NULL)))
	{
		MessageBox(0, "DirectInputキーボード初期化に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}

	//	データフォーマット
	if (FAILED(m_pMouseDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);					// 包含する構造体のサイズ
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);			// DIPROPHEADER 構造体のサイズ
	diprop.diph.dwObj = 0;									// アクセスするプロパティが属するオブジェクト
	diprop.diph.dwHow = DIPH_DEVICE;						// dwObj メンバの解釈方法を指定する値
	diprop.dwData = 1000;									// 設定または取得されるプロパティ値
	//	diprop.dwData		= DIPROPAXISMODE_ABS;	// 絶対値モードの場合
	if (FAILED(m_pMouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph)))
	{
		MessageBox(0, "軸モードの設定に失敗", NULL, MB_OK);
		return E_FAIL;
	}

	//	協調レベル
	if (FAILED(m_pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	// アクセス許可
	m_pMouseDevice->Acquire();
	return S_OK;
}
