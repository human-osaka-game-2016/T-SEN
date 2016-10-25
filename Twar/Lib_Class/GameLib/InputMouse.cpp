/**
* @file   InputMouse.cpp
* @brief  マウス操作に関するクラス.
* @author haga
*/
#include "InputDevice.h"
#include "InputMouse.h"

// コンストラクタ
InputMouse::InputMouse() :
m_pMouseDevice(InputDevice::GetInstance().GetMouseDevice()),
m_hWnd(InputDevice::GetInstance().GethWnd())
{
	// クライアントサイズを取得
	RECT rec;		
	GetClientRect(m_hWnd,&rec);
	m_wndWid = rec.right - rec.left;
	m_wndHgt = rec.bottom - rec.top;
	m_posX = m_wndWid / 2;
	m_posY = m_wndHgt / 2;
	m_wheel = 0;
	m_LDown = false;
	m_RDown = false;
	m_MDown = false;
	m_LAction = false;
	m_MAction = false;
	m_RAction = false;

	for (int i = 0 ; i < MOUSEBUTTON::ButtonMAX; i++)
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
	m_wheel = 0;

	DIDEVICEOBJECTDATA od;			// デバイスオブジェクトデータを格納する変数
	DWORD dwItems = 1;
	HRESULT hr;

	// クライアントサイズを取得
	RECT rec;
	GetWindowRect(m_hWnd, &rec);

	while (true)
	{
		hr = m_pMouseDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &dwItems, 0);
		if (hr == DIERR_INPUTLOST)
		{
			m_pMouseDevice->Acquire();
		}
		else if (FAILED(hr) || dwItems == 0)
		{
			if (hr == DIERR_NOTACQUIRED)
			{
				m_pMouseDevice->Acquire();
			}
			break;
		}
		else
		{
			POINT pos;				// 入手したマウス座標を一時的に格納する変数
			
			switch (od.dwOfs)
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

				m_wheel = od.dwData;
				if (m_wheel > 0)
				{
					m_wheel = 1;
				}
				else if (m_wheel < 0)
				{
					m_wheel = -1;
				}
				break;

			case DIMOFS_BUTTON0:					// 左ボタンの状態
				m_LDown = (od.dwData & 0x80) ? true : false;
				if (m_LDown)
				{
					m_LAction = true;
				}
				else
				{
					m_LAction = false;
				}
				break;

			case DIMOFS_BUTTON1:					// 右ボタンの状態
				m_RDown = (od.dwData & 0x80) ? true : false;
				if (m_RDown)
				{
					m_RAction = true;
				}
				else
				{
					m_RAction = false;
				}
				break;

			case DIMOFS_BUTTON2:					// 中ボタンの状態
				m_MDown = (od.dwData & 0x80) ? true : false;
				if (m_MDown)
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

	switch (mouseButton)
	{
	case MouseLeft:
		mouseClick = GetIsLAction();
		break;

	case MouseRight:
		mouseClick = GetIsLAction();
		break;

	case MouseCenter:
		mouseClick = GetIsMAction();
		break;
	}

	if (mouseClick)
	{
		if (m_PreMouse[mouseButton] == BTN_OFF)
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
		if (m_PreMouse[mouseButton] == BTN_ON)
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
	if (m_wheel > 0)
	{
		return WHEEL_UP;
	}
	else if (m_wheel < 0)
	{
		return WHEEL_DOWN;
	}

	return WHEEL_NONE;
}