/**
* @file InputKey.cpp
* @brief  操作キーに関するクラスのcpp
* @author haga
*/
#include <dinput.h>
#include "InputDevice.h"
#include "InputKey.h"

// コンストラクタ
InputKey::InputKey() : m_pKeyDevice(InputDevice::GetInstance().GetKeyDevice())
{
	for (int i = 0; i < KEYMAX;i++)
	{
		m_PreKey[i] = OFF;
	} 
}

// デストラクタ
InputKey::~InputKey()
{
}

// キーの更新
void InputKey::UpdateKey()
{
	HRESULT hr = m_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pKeyDevice->GetDeviceState(sizeof(m_diks), &m_diks);
	}
}

// キー状態確認関数
void InputKey::KeyCheck(BYTE* DIK, KEYKIND st)
{
	if ((*DIK) & 0x80)
	{
		if (m_PreKey[st] == OFF)
		{
			m_Key[st] = PUSH;
		
		}
		else
		{
			m_Key[st] = ON;
		}
		m_PreKey[st] = ON;
	}
	else
	{
		if (m_PreKey[st] == ON)
		{
			m_Key[st] = RELEASE;
		}
		else
		{
			m_Key[st] = OFF;
		}
		m_PreKey[st] = OFF;
	}
}