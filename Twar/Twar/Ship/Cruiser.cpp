/**
	@file ShipManager.cpp
	@brief ShipManagerクラスcpp
	@author kawaguchi
*/

#include "Cruiser.h"
#include "GameLib/GameLib.h"
#include "Fbx/FbxModel.h"
#include "State/StateMachine.h"
#include "../Collision/Collision.h"

const float Cruiser::m_SpeedLimit = 1.5f;

Cruiser::Cruiser(D3DXVECTOR3* pos)
	: Ship(pos, { 600, 0.f })
{
	m_PitchSpeed = 0.025f;
	m_PitchUpperLimit = -4.f;
	m_PitchLowerLimit = -2.f;
	m_ObjPos.y = m_PitchLowerLimit + (m_PitchUpperLimit - m_PitchLowerLimit) / 2;
	m_pCollision = new Collision(30.f, Collision::SHIP);
	m_pStateMachine = new StateMachine(m_ObjPos, m_Rotate, m_Slant, m_SpeedLimit);
}


Cruiser::~Cruiser()
{
	delete m_pStateMachine;
	delete m_pCollision;
}


void Cruiser::Control()
{
	JudgeColllision();

	switch (m_Attr)
	{
	case Ship::PLAYER:
		Cruiser::ControlPlayer();
		break;

	case Ship::ALLY:
		Cruiser::ControlAlly();
		break;

	case Ship::ENEMY:
		Cruiser::ControlEnemy();
		break;
	}

	static bool IsUp = false;

	if (IsUp)
	{
		m_ObjPos.y += m_PitchSpeed;

		if (m_ObjPos.y >= m_PitchLowerLimit)
		{
			IsUp = false;
		}
	}
	else
	{
		m_ObjPos.y -= m_PitchSpeed;

		if (m_ObjPos.y <= m_PitchUpperLimit)
		{
			IsUp = true;
		}
	}

	m_pCollision->SetData(m_ObjPos);
}

void Cruiser::JudgeColllision()
{
	if(m_pCollision->InformCollision())
	{
		m_Status.m_Hp -= 30;
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//		プレイヤー
//
//----------------------------------------------------------------------------------------------------------------------
void Cruiser::ControlPlayer()
{
	D3DXVECTOR3 vecAxisZ{ 0.f, 0.f, 1.f };			//!<	単位ベクトル

	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Rotation);

	if (m_pGameLib.ChecKMouseR() == ON)
	{
		m_Angle = m_ZoomAngle;
		m_IsZoom = true;
	}
	else if (m_pGameLib.ChecKMouseR() == OFF)
	{
		m_Angle = m_NormalAngle;
		m_IsZoom = false;
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

	if (m_Rotate >= 360.f)						//!<	360 = 一回転の角度
	{
		m_Rotate -= 360.f;
		m_CameraRotate -= 360.f;
	}
	if (m_Rotate <= -360.f)
	{
		m_Rotate += 360.f;
		m_CameraRotate += 360.f;
	}

	m_ObjPos += vecAxisZ * m_Status.m_Speed;

	POINT newCursor;
	GetCursorPos(&newCursor);

	HWND hWnd = InputDevice::GetInstance().GethWnd();

	RECT winRect;
	RECT clientRect;
	GetWindowRect(hWnd, &winRect);
	GetClientRect(hWnd, &clientRect);
	int centerPosX = static_cast<int>(winRect.left + ((clientRect.right - clientRect.left) / 2));
	int centerPosY = static_cast<int>(winRect.bottom - ((clientRect.bottom - clientRect.top) / 2));


	float nextLookatPos = m_LookatPos.y - (newCursor.y - centerPosY) * 0.05f;			//!<	0.05	仮の感度(ゲーム中に変更できるようにする、かもしれない)

	if (nextLookatPos <= 100.f && nextLookatPos >= 25.f)							//!<	100, 25	目で見て決めたカメラの上限と下限
	{
		m_LookatPos.y = nextLookatPos;
	}

	float nextRotate = m_CameraRotate + (newCursor.x - centerPosX) * 0.05f;			//!<	0.05	仮の感度(ゲーム中に変更できるようにする、かもしれない)

	if (nextRotate <= m_Rotate + 150.f && nextRotate >= m_Rotate - 150.f)		//!<	150		船の前方から見える角度(左右150°ずつ)
	{
		m_CameraRotate = nextRotate;
	}
	else if (nextRotate >= m_Rotate + 150.f)
	{
		m_CameraRotate = m_Rotate + 150.f;
	}
	else if (nextRotate <= m_Rotate - 150.f)
	{
		m_CameraRotate = m_Rotate - 150.f;
	}

	m_CameraPos.x = m_LookatPos.x = m_ObjPos.x;
	m_CameraPos.z = m_LookatPos.z = m_ObjPos.z;
}

//----------------------------------------------------------------------------------------------------------------------
//
//		味方
//
//----------------------------------------------------------------------------------------------------------------------
void Cruiser::ControlAlly()
{
	m_pStateMachine->SetStatus(m_Status);
	m_pStateMachine->Update();
	m_Rotate = m_pStateMachine->GetAngle();
	m_Slant = m_pStateMachine->GetSlant();
	m_ObjPos = m_pStateMachine->GetPos();
	m_Status = m_pStateMachine->GetStatus();
}

//----------------------------------------------------------------------------------------------------------------------
//
//		敵
//
//----------------------------------------------------------------------------------------------------------------------
void Cruiser::ControlEnemy()
{
	m_pStateMachine->SetStatus(m_Status);
	m_pStateMachine->Update();
	m_Rotate = m_pStateMachine->GetAngle();
	m_Slant = m_pStateMachine->GetSlant();
	m_ObjPos = m_pStateMachine->GetPos();
	m_Status = m_pStateMachine->GetStatus();
}

void Cruiser::Draw()
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

