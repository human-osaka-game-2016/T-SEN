/**
	@file ShipManager.cpp
	@brief ShipManagerクラスcpp
	@author kawaguchi
*/

#include "BattleShip.h"
#include "GameLib/GameLib.h"
#include "Fbx/FbxModel.h"

const float BattleShip::m_SpeedLimit = 1.f;

BattleShip::BattleShip(D3DXVECTOR3* pos)
	: Ship(pos, { 7500, 0.f})
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

	if (m_IsUp)
	{
		m_ObjPos.y += m_PitchSpeed;
		
		if (m_ObjPos.y >= m_PitchLowerLimit)
		{
			m_IsUp = false;
		}
	}
	else
	{
		m_ObjPos.y -= m_PitchSpeed;

		if (m_ObjPos.y <= m_PitchUpperLimit)
		{
			m_IsUp = true;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//		プレイヤー
//
//----------------------------------------------------------------------------------------------------------------------
void BattleShip::ControlPlayer()
{
	D3DXVECTOR3 vecAxisZ{ 0.f, 0.f, 1.f };			//!<	単位ベクトル

	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Rotation);

	if (m_pGameLib.ChecKMouseR() == PUSH)
	{
		m_Angle = m_ZoomAngle;
		m_IsZoom = true;
	}
	else if (m_pGameLib.ChecKMouseR() == RELEASE)
	{
		m_Angle = m_NormalAngle;
		m_IsZoom = false;
	}

	if (m_Rotate == 360.f)						//!<	360 = 一回転の角度
	{
		m_Rotate -= 360.f;
		m_CameraRotate -= 360.f;
	}
	if (m_Rotate == -360.f)
	{
		m_Rotate += 360.f;
		m_CameraRotate += 360.f;
	}


	float nextSpeed;

	if (m_pGameLib.CheckKey(DIK_W, W) - OFF + m_pGameLib.CheckKey(DIK_S, S) - OFF)
	{
		if (m_pGameLib.CheckKey(DIK_W, W) == ON)
		{
			nextSpeed = m_Status.m_Speed + m_SpeedLimit / m_LimitArrivalFlame;

			if (nextSpeed >= m_SpeedLimit)
			{
				m_Status.m_Speed = m_SpeedLimit;
			}
			else if (nextSpeed < m_SpeedLimit)
			{
				m_Status.m_Speed = nextSpeed;
			}
		}
		else
		{
			nextSpeed = m_Status.m_Speed - m_DecelerationSpeed;

			if (nextSpeed > 0)
			{
				m_Status.m_Speed = nextSpeed;
			}
		}

		if (m_pGameLib.CheckKey(DIK_S, S) == ON)
		{
			nextSpeed = m_Status.m_Speed - m_SpeedLimit / m_LimitArrivalFlame;

			if (nextSpeed <= -m_SpeedLimit)
			{
				m_Status.m_Speed = -m_SpeedLimit;
			}
			else if (nextSpeed > -m_SpeedLimit)
			{
				m_Status.m_Speed = nextSpeed;
			}
		}
		else
		{
			nextSpeed = m_Status.m_Speed + m_DecelerationSpeed;

			if (nextSpeed < 0)
			{
				m_Status.m_Speed = nextSpeed;
			}
		}
	}
	else
	{
		if (m_Status.m_Speed > 0)
		{
			nextSpeed = m_Status.m_Speed - m_DecelerationSpeed;

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
			nextSpeed = m_Status.m_Speed + m_DecelerationSpeed;

			if (nextSpeed > 0)
			{
				m_Status.m_Speed = 0;
			}
			else
			{
				m_Status.m_Speed += m_DecelerationSpeed;
			}
		}
	}

	float nextSlant;
	float RotateSpeed;												//!<	速度に依存する
	float tiltSpeed;												//!<	速度に依存する
	RotateSpeed = tiltSpeed = m_Status.m_Speed * 0.5f;				//!<	0.5		目で見て導き出された結果
	float slantLimit = tiltSpeed * 10.f;							//!<	10.0	傾く速度が限界の1/10くらいが妥当かと

	if (m_Status.m_Speed > 0)
	{
		if (m_pGameLib.CheckKey(DIK_A, A) == ON)
		{
			nextSlant = m_Slant + tiltSpeed;

			m_Rotate -= RotateSpeed;
			m_CameraRotate -= RotateSpeed;

			if (m_IsLeftSlantLimit)
			{
				m_Slant = slantLimit;
			}
			else if (nextSlant >= slantLimit)
			{
				m_Slant += tiltSpeed;
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

			if (m_Slant > 0)
			{
				nextSlant = m_Slant - tiltSpeed;

				if (nextSlant < 0)
				{
					m_Slant = 0.f;
				}
				else
				{
					m_Slant = nextSlant;
				}
			}
		}

		if (m_pGameLib.CheckKey(DIK_D, D) == ON)
		{
			nextSlant = m_Slant - tiltSpeed;

			m_Rotate += RotateSpeed;
			m_CameraRotate += RotateSpeed;

			if (m_IsRightSlantLimit)
			{
				m_Slant = -slantLimit;
			}
			else if (nextSlant <= -slantLimit)
			{
				m_Slant -= tiltSpeed;
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

			if (m_Slant < 0)
			{
				nextSlant = m_Slant + tiltSpeed;

				if (nextSlant > 0)
				{
					m_Slant = 0.f;
				}
				else
				{
					m_Slant = nextSlant;
				}
			}
		}
	}
	else if (m_Status.m_Speed < 0)
	{
		if (m_pGameLib.CheckKey(DIK_A, A) == ON)
		{
			nextSlant = m_Slant - tiltSpeed;

			m_Rotate -= RotateSpeed;
			m_CameraRotate -= RotateSpeed;

			if (m_IsLeftSlantLimit)
			{
				m_Slant = -slantLimit;
			}
			else if (nextSlant >= -slantLimit)
			{
				m_Slant -= tiltSpeed;
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

			if (m_Slant > 0)
			{
				nextSlant = m_Slant + tiltSpeed;

				if (nextSlant < 0)
				{
					m_Slant = 0.f;
				}
				else
				{
					m_Slant = nextSlant;
				}
			}
		}

		if (m_pGameLib.CheckKey(DIK_D, D) == ON)
		{
			nextSlant = m_Slant + tiltSpeed;

			m_Rotate += RotateSpeed;
			m_CameraRotate += RotateSpeed;

			if (m_IsRightSlantLimit)
			{
				m_Slant = slantLimit;
			}
			else if (nextSlant <= slantLimit)
			{
				m_Slant += tiltSpeed;
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

			if (m_Slant < 0)
			{
				nextSlant = m_Slant - tiltSpeed;

				if (nextSlant > 0)
				{
					m_Slant = 0.f;
				}
				else
				{
					m_Slant = nextSlant;
				}
			}
		}
	}

	m_ObjPos += vecAxisZ * m_Status.m_Speed;

	float mousePosX, mousePosY;

	m_pGameLib.GetMousePos(&mousePosX, &mousePosY);

	HWND hWnd = InputDevice::GetInstance().GethWnd();
	RECT rect;
	GetClientRect(hWnd, &rect);
	ClientToScreen(hWnd, (LPPOINT)rect.left);
	ClientToScreen(hWnd, (LPPOINT)rect.right);

	float centerPosX = ((rect.right - rect.left) / 2) + rect.left;
	float centerPosY = ((rect.bottom - rect.top) / 2) + rect.top;

	float nextLookPos = m_LookatPos.y - (mousePosY - centerPosX) * 0.05f;			//!<	0.05	仮の感度(ゲーム中に変更できるようにする、かもしれない)

	if (nextLookPos <= 100.f && nextLookPos >= 25.f)							//!<	100, 25	目で見て決めたカメラの上限と下限
	{
		m_LookatPos.y = nextLookPos;
	}

	//float nextRotate = m_CameraRotate + (mousePosX - centerPosY) * 0.05f;			//!<	0.05	仮の感度(ゲーム中に変更できるようにする、かもしれない)

	//if (nextRotate <= m_Rotate + 150.f && nextRotate >= m_Rotate - 150.f)		//!<	150		船の前方から見える角度(左右150°ずつ)
	//{
	//	m_CameraRotate = nextRotate;
	//}

	m_CameraPos.x = m_LookatPos.x = m_ObjPos.x;
	m_CameraPos.z = m_LookatPos.z = m_ObjPos.z;
}

//----------------------------------------------------------------------------------------------------------------------
//
//		味方
//
//----------------------------------------------------------------------------------------------------------------------
void BattleShip::ControlAlly()
{
}

//----------------------------------------------------------------------------------------------------------------------
//
//		敵
//
//----------------------------------------------------------------------------------------------------------------------
void BattleShip::ControlEnemy()
{
}

void BattleShip::Draw()
{
	D3DXMatrixRotationY(&m_Rotation, m_Rotate * 3.141592f / 180.f);						//	円周率
	D3DXMatrixRotationZ(&m_Slope, m_Slant * 3.141592f / 180.f);							//	円周率
	D3DXMatrixRotationY(&m_CameraRotation, m_CameraRotate * 3.141592f / 180.f);			//	円周率
	TransWorld();		// ワールド座標変換
	if (!m_IsZoom)
	{
		m_pFbx->DrawFbx();
	}
}

