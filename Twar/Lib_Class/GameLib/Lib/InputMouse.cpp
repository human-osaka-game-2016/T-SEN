/**
* @file		InputMouse.cpp
* @brief	InputMouseクラス実装
* @author	haga
*/
#include "InputMouse.h"

// コンストラクタ
InputMouse::InputMouse()
	: m_pMouseDevice(InputDevice::GetInstance().GetMouseDevice())
	, m_hWnd(InputDevice::GetInstance().GethWnd())
	, m_Wheel(0)
	, m_LDown(false)
	, m_RDown(false)
	, m_MDown(false)
	, m_LAction(false)
	, m_MAction(false)
	, m_RAction(false)
{
	// クライアントサイズを取得
	RECT rect;
	GetClientRect(m_hWnd, &rect);
	m_wndWid = rect.right - rect.left;
	m_wndHgt = rect.bottom - rect.top;
	m_posX = m_wndWid / 2;
	m_posY = m_wndHgt / 2;

	for(int i = 0; i < MOUSEBUTTON::ButtonMAX; i++)
	{
		m_PreMouse[i] = BTN_STATE::BTN_OFF;
		m_mouse[i] = BTN_STATE::BTN_OFF;
	}
}

// デストラクタ
InputMouse::~InputMouse()
{
}

// マウスのデータ更新
void InputMouse::UpdateMouse()
{
	m_Wheel = 0;

	DIDEVICEOBJECTDATA od;			// デバイスオブジェクトデータを格納する変数
	DWORD dwItems = 1;
	HRESULT hr;

	while(true)
	{
		hr = m_pMouseDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &dwItems, 0);
		if(hr == DIERR_INPUTLOST)
		{
			m_pMouseDevice->Acquire();
		}
		else if(FAILED(hr) || dwItems == 0)
		{
			if(hr == DIERR_NOTACQUIRED)
			{
				m_pMouseDevice->Acquire();
			}
			break;
		}
		else
		{
			POINT pos;				// 入手したマウス座標を一時的に格納する変数

			switch(od.dwOfs)
			{
			case DIMOFS_X:							// マウスの水平移動
				GetCursorPos(&pos);					// マウス座標を取得する
				ScreenToClient(m_hWnd, &pos);		// スクリーン座標からクライアント座標へと変更する
				m_posX = pos.x;
				break;

			case DIMOFS_Y:							// マウスの垂直移動
				GetCursorPos(&pos);
				ScreenToClient(m_hWnd, &pos);
				m_posY = pos.y;
				break;

			case DIMOFS_Z:							// マウスのZ(ホイール)動作

				m_Wheel = od.dwData;
				if(m_Wheel > 0)
				{
					m_Wheel = 1;
				}
				else if(m_Wheel < 0)
				{
					m_Wheel = -1;
				}
				break;

			case DIMOFS_BUTTON0:					// 左ボタンの状態
				m_LDown = ( od.dwData & 0x80 ) ? true : false;
				if(m_LDown)
				{
					m_LAction = true;
				}
				else
				{
					m_LAction = false;
				}
				break;

			case DIMOFS_BUTTON1:					// 右ボタンの状態
				m_RDown = ( od.dwData & 0x80 ) ? true : false;
				if(m_RDown)
				{
					m_RAction = true;
				}
				else
				{
					m_RAction = false;
				}
				break;

			case DIMOFS_BUTTON2:					// 中ボタンの状態
				m_MDown = ( od.dwData & 0x80 ) ? true : false;
				if(m_MDown)
				{
					m_MAction = true;
				}
				else
				{
					m_MAction = false;
				}
				break;

			}
		}

	}
}


// 状態を確認する関数
void InputMouse::CheckState(MOUSEBUTTON mouseButton)
{
	bool mouseClick = false;		// マウスがクリックされたか

	switch(mouseButton)
	{
	case MouseLeft:
		mouseClick = GetIsLAction();
		break;

	case MouseRight:
		mouseClick = GetIsRAction();
		break;

	case MouseCenter:
		mouseClick = GetIsMAction();
		break;
	}

	if(mouseClick)
	{
		if(m_PreMouse[mouseButton] == BTN_OFF)
		{
			m_mouse[mouseButton] = BTN_PUSH;
		}
		else
		{
			m_mouse[mouseButton] = BTN_ON;
		}
		m_PreMouse[mouseButton] = BTN_ON;
	}
	else
	{
		if(m_PreMouse[mouseButton] == BTN_ON)
		{
			m_mouse[mouseButton] = BTN_RELEASE;
		}
		else
		{
			m_mouse[mouseButton] = BTN_OFF;
		}
		m_PreMouse[mouseButton] = BTN_OFF;
	}
}

BTN_STATE InputMouse::ChecKMouse(MOUSEBUTTON mouseButton)
{

	CheckState(mouseButton);

	return m_mouse[mouseButton];
}

WHEELSTATE InputMouse::GetWheelState()
{
	if(m_Wheel > 0)
	{
		return WHEEL_UP;
	}
	else if(m_Wheel < 0)
	{
		return WHEEL_DOWN;
	}

	return WHEEL_NONE;
}

// マウスのカーソルを描画するかどうかを決める関数
void InputMouse::ShowMouseCursor(bool isVisible)
{
	ShowCursor(isVisible);
}

// マウスの座標をセットする関数
void InputMouse::SetMouseCursor(int x, int y)
{
	HWND currentWnd = GetActiveWindow();		// 現在アクティブであるウィンドウのハンドルを取得する

	if(currentWnd == m_hWnd)					// ゲームウィンドウがアクティブかどうか
	{
		SetCursorPos(x, y);
	}
}

// マウスの座標を中心に持ってくる
void InputMouse::SetMouseCenter()
{
	HWND currentWnd = GetActiveWindow();		// 現在アクティブであるウィンドウのハンドルを取得する

	if(currentWnd == m_hWnd)					// ゲームウィンドウがアクティブかどうか
	{
		RECT winRect;
		RECT clientRect;
		GetWindowRect(m_hWnd, &winRect);
		GetClientRect(m_hWnd, &clientRect);
		int mousePosX = static_cast<int>( ( ( clientRect.right - clientRect.left ) / 2 ) + winRect.left );
		int mousePosY = static_cast<int>( ( ( clientRect.bottom - clientRect.top ) / 2 ) + winRect.top );
		SetCursorPos(mousePosX, mousePosY);
	}
}

/**マウスの動く範囲をウィンドウ内に制限する関数*/
void InputMouse::RestrictCursor()
{
	HWND currentWnd = GetActiveWindow();			// 現在アクティブであるウィンドウのハンドルを取得する

	if(currentWnd == m_hWnd)						// ゲームウィンドウがアクティブかどうか
	{
		// ウィンドウサイズを取得
		RECT rec;
		GetWindowRect(m_hWnd, &rec);
		ClipCursor(&rec);
	}
	else
	{
		ClipCursor(NULL);
	}
}