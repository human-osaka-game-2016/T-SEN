#include "GameLib/GameLib.h"
#include "BattleShip.h"


BattleShip::BattleShip(D3DXVECTOR3* pos):
Ship(pos, {7500, 0.f})
{
}


BattleShip::~BattleShip()
{
}

void BattleShip::Control()
{
	switch (m_Attr)
	{
	case Ship::PLAYER:
		BattleShip::ControlPlayer();
		break;

	case Ship::ALLY:
		BattleShip::ControlAlly();
		break;

	case Ship::ENEMY:
		BattleShip::ControlEnemy();
		break;
	}

	static bool IsUp = false;

	if (IsUp)
	{
		m_ObjPos.y += 0.025f;
		
		if (m_ObjPos.y >= -2.f)
		{
			IsUp = false;
		}
	}
	else
	{
		m_ObjPos.y -= 0.025f;

		if (m_ObjPos.y <= -6.f)
		{
			IsUp = true;
		}
	}
}

void BattleShip::ControlPlayer()
{
	D3DXVECTOR3 vecAxisZ{ 0.f, 0.f, 1.f };

	POINT newCursor;

	m_InputKey.UpdateKey();
	m_Mouse.UpdateMouse();

	m_InputKey.CheckKey(DIK_W, W);
	m_InputKey.CheckKey(DIK_S, S);
	m_InputKey.CheckKey(DIK_D, D);
	m_InputKey.CheckKey(DIK_A, A);

	GetCursorPos(&newCursor);

	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Rotation);


	if (GameLib::Instance().ChecKMouseR() == PUSH)
	{
		m_Angle = 10.f;
		m_IsZoom = true;
	}
	if (GameLib::Instance().ChecKMouseR() == OFF)
	{
		m_Angle = 50.f;
		m_IsZoom = false;
	}

	if (m_Rotate == 360.f)
	{
		m_Rotate -= 360.f;
		m_CameraRotate -= 360.f;
	}
	if (m_Rotate == -360.f)
	{
		m_Rotate += 360.f;
		m_CameraRotate += 360.f;
	}


	if (m_InputKey.m_Key[W] == BTN_ON)
	{
		if (m_Status.m_Speed == m_SpeedLimit)
		{
			m_Status.m_Speed += m_SpeedLimit / 500.f;
		}
		else if (m_Status.m_Speed < m_SpeedLimit)
		{
			m_Status.m_Speed += m_SpeedLimit / 500.f * 2;
		}

	}

	if (m_InputKey.m_Key[S] == BTN_ON)
	{
		if (m_Status.m_Speed == -1.f)
		{
			m_Status.m_Speed -= m_SpeedLimit / 500.f;
		}
		else if (m_Status.m_Speed > -1.f)
		{
			m_Status.m_Speed -= m_SpeedLimit / 500.f * 2;
		}
	}

	float nextSlant;
	float tiltSpeed;

	if (m_Status.m_Speed != 0)
	{

		float nextSpeed = m_Status.m_Speed - m_DecelerationSpeed;

		if (m_Status.m_Speed > 0)
		{
			if (nextSpeed < 0)
			{
				m_Status.m_Speed = 0;
			}
			else
			{
				m_Status.m_Speed -= m_DecelerationSpeed;
			}
		}
		else if (m_Status.m_Speed < 0)
		{
			if (nextSpeed > 0)
			{
				m_Status.m_Speed = 0;
			}
			else
			{
				m_Status.m_Speed += m_DecelerationSpeed;
			}
		}

		tiltSpeed = m_Status.m_Speed;
		m_RotateSpeed = tiltSpeed * 0.5;

		if (m_InputKey.m_Key[A] == BTN_ON)
		{
			nextSlant = m_Slant + tiltSpeed;

			m_Rotate -= m_RotateSpeed;
			m_CameraRotate -= m_RotateSpeed;

			if(m_IsLeftSlantLimit)
			{
				m_Slant = tiltSpeed * 5;
			}
			else if (nextSlant >= tiltSpeed * 5)
			{
				m_Slant += tiltSpeed * 0.5f;
				m_IsLeftSlantLimit = true;
			}
			else
			{
				m_Slant = nextSlant;
			}
		}
		else
		{
			m_IsLeftSlantLimit = false;
		}

		if (m_InputKey.m_Key[D] == BTN_ON)
		{
			nextSlant = m_Slant - tiltSpeed;

			m_Rotate += m_RotateSpeed;
			m_CameraRotate += m_RotateSpeed;

			if (m_IsRightSlantLimit)
			{
				m_Slant = tiltSpeed * -5;
			}
			else if (nextSlant <= tiltSpeed * -5)
			{
				m_Slant -= tiltSpeed * 0.5f;
				m_IsRightSlantLimit = true;
			}
			else
			{
				m_Slant = nextSlant;
			}
		}
		else
		{
			m_IsRightSlantLimit = false;
		}
	}

	tiltSpeed = m_Status.m_Speed;
	nextSlant = m_Slant - tiltSpeed * 0.5f;

	if (m_Slant != 0)
	{
		if (m_Slant > 0)
		{
			if (nextSlant < 0)
			{
				m_Slant = 0.f;
			}
			else
			{
				m_Slant -= tiltSpeed * 0.5f;
			}
		}
		else if (m_Slant < 0)
		{
			if (nextSlant > 0)
			{
				m_Slant = 0.f;
			}
			else
			{
				m_Slant += tiltSpeed * 0.5f;
			}
		}
	}

	m_ObjPos += vecAxisZ * m_Status.m_Speed;

	float nextLookPos = m_LookatPos.y - (newCursor.y - 450.f) * 0.05f;

	if (nextLookPos <= 100.f && nextLookPos >= 25.f)
	{
		m_LookatPos.y = nextLookPos;
	}

	float nextRotate = m_CameraRotate + (newCursor.x - 800.f) * 0.05f;

	if (nextRotate <= m_Rotate + 150.f && nextRotate >= m_Rotate - 150.f)
	{
		m_CameraRotate = nextRotate;
	}

	m_CameraPos.x = m_LookatPos.x = m_ObjPos.x;
	m_CameraPos.z = m_LookatPos.z = m_ObjPos.z;

	SetCursorPos(800, 450);
}

void BattleShip::ControlAlly()
{
}

void BattleShip::ControlEnemy()
{
}

void BattleShip::Draw()
{
	D3DXMatrixRotationY(&m_Rotation, m_Rotate * 3.141592f / 180.f);
	D3DXMatrixRotationZ(&m_Slope, m_Slant * 3.141592f / 180.f);
	D3DXMatrixRotationY(&m_CameraRotation, (m_CameraRotate) * 3.141592f / 180.f);
	TransWorld();		// ワールド座標変換
	if (!m_IsZoom)
	{
		m_pFbx->DrawFbx();
	}
}

