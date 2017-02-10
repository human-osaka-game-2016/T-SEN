/**
@file ShipManager.cpp
@brief ShipManagerクラスcpp
@author kawaguchi
*/

#include "Cruiser.h"
#include "GameLib/GameLib.h"
#include "Fbx/FbxModel.h"
#include "../StateMachine/ShipStateManager.h"
#include "../BattleData/BattleDataManager.h"
#include "../Bullet/BulletManager.h"

Cruiser::Cruiser(D3DXVECTOR3* pos, BulletManager* pBulletManager)
	: Ship(pos, { 2500, 0.f }, SHIP_ID::CRUISER, pBulletManager)
{
	m_SpeedLimit = m_CruiserSpeedLimit;
	m_pStateMachine = new StateMachine<Ship>(this);
	m_pStateMachine->SetCurrntState(ShipStateManager::GetShipState(ShipStateManager::MOVE_TO_TARGET));
	m_pStateMachine->EnterCurrentState();
	m_pStateMachine->SetPreviousState(ShipStateManager::GetShipState(ShipStateManager::MOVE_TO_TARGET));
}


Cruiser::~Cruiser()
{
	delete m_pStateMachine;
	m_pStateMachine = nullptr;
}


void Cruiser::Control()
{
	if (!m_IsHit)
	{
		switch (m_Attr)
		{
		case Ship::PLAYER:
			Cruiser::ControlPlayer();
			BattleDataManager::Instance().SetPlayerHp(m_Status.m_Hp);
			BattleDataManager::Instance().SetPlayerSpeed(m_Status.m_Speed);
			break;

		case Ship::ALLY:
			Cruiser::ControlAlly();
			break;

		case Ship::ENEMY:
			Cruiser::ControlEnemy();
			break;
		}
	}
	else
	{
		switch(m_Attr)
		{
		case Ship::PLAYER:
		{
			D3DXVECTOR3 vecAxisZ{ 0.f, 0.f, 1.f };			//!<	単位ベクトル
			D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Rotation);

		//		m_ObjPos = m_OldObjPos;
		//		m_CameraPos.x = m_LookatPos.x = m_ObjPos.x;
		//		m_CameraPos.z = m_LookatPos.z = m_ObjPos.z;
		//
		//		m_Status.m_Speed = 0.f;
		//		m_Slant = 0.f;
		//		m_Rotate = m_OldRotate;

		m_Status.m_Speed *= -1.f;
		m_ObjPos += vecAxisZ * m_Status.m_Speed;
		m_CameraPos.x = m_LookatPos.x = m_ObjPos.x;
		m_CameraPos.z = m_LookatPos.z = m_ObjPos.z;
		m_Rotate = m_OldRotate;

			m_IsHit = false;
		}
			break;

		case Ship::ALLY:
		{
			if(m_pStateMachine->GetCurrntState() != ShipStateManager::GetShipState(ShipStateManager::AVOID_OBJECT))
			{
				m_pStateMachine->SetCurrntState(ShipStateManager::GetShipState(ShipStateManager::AVOID_OBJECT));
				m_pStateMachine->EnterCurrentState();
			}
			else
			{
				m_pStateMachine->Update();
				m_IsHit = false;
			}
		}
		break;

		case Ship::ENEMY:
		{
			if(m_pStateMachine->GetCurrntState() != ShipStateManager::GetShipState(ShipStateManager::AVOID_OBJECT))
			{
				m_pStateMachine->SetCurrntState(ShipStateManager::GetShipState(ShipStateManager::AVOID_OBJECT));
				m_pStateMachine->EnterCurrentState();
			}
			else
			{
				m_pStateMachine->Update();
				m_IsHit = false;
			}
		}
			break;
		}
	}

	if (m_IsUp)
	{
		m_ObjPos.y += m_PitchSpeed;

		if (m_ObjPos.y >= m_PitchLowerLimit + 1.f)
		{
			m_IsUp = false;
		}
	}
	else
	{
		m_ObjPos.y -= m_PitchSpeed;

		if (m_ObjPos.y <= m_PitchUpperLimit + 3.f)
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
void Cruiser::ControlPlayer()
{
	D3DXVECTOR3 vecAxisZ{ 0.f, 0.f, 1.f };			//!<	単位ベクトル

	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Rotation);

	///////////////////////////////////////////////　ここから　/////////////////////////////////////////////////////////

	if (m_pGameLib.CheckKey(DIK_P, P) == PUSH)
	{
		if (m_IsFpsMode)
		{
			m_IsFpsMode = false;
			m_CameraPos.y += 25.f;
			m_LookatPos.y += 25.f;
		}
		else
		{
			m_IsFpsMode = true;
			m_CameraPos.y -= 25.f;
			m_LookatPos.y -= 25.f;
		}
	}

	if (m_pGameLib.ChecKMouseR() == ON)
	{
		m_Angle = m_ZoomAngle;
		if (!m_IsZoom)
		{
			if (!m_IsFpsMode)
			{
				m_CameraPos.y -= 25.f;
				m_LookatPos.y -= 25.f;
			}
		}
		m_IsZoom = true;
	}
	else if (m_pGameLib.ChecKMouseR() == OFF)
	{
		m_Angle = m_NormalAngle;
		if (m_IsZoom)
		{
			if (!m_IsFpsMode)
			{
				m_CameraPos.y += 25.f;
				m_LookatPos.y += 25.f;
			}
		}
		m_IsZoom = false;

		if (m_pGameLib.CheckKey(DIK_P, P) == PUSH)
		{
			if (m_IsFpsMode)
			{
				m_IsFpsMode = false;
				m_CameraPos.y += 25.f;
				m_LookatPos.y += 25.f;
			}
			else
			{
				m_IsFpsMode = true;
				m_CameraPos.y -= 25.f;
				m_LookatPos.y -= 25.f;
			}
		}
	}

	if (m_pGameLib.ChecKMouseL() == ON && m_FiringCount == 0)
	{
		D3DXVECTOR3 vec;
		if (m_CameraPos.y > m_LookatPos.y)
		{
			vec.x = m_LookatPos.x - m_CameraPos.x;
			vec.y = 0.f;
			vec.z = m_LookatPos.z - m_CameraPos.z;
		}
		else
		{
			vec.x = m_LookatPos.x - m_CameraPos.x;
			vec.y = m_LookatPos.y - m_CameraPos.y;
			vec.z = m_LookatPos.z - m_CameraPos.z;
		}
		if (m_IsFpsMode)
		{
			m_pBulletManager->Create({ m_CameraPos.x, m_CameraPos.y, m_CameraPos.z },
				m_CameraRotate,
				&vec);
		}
		else if (m_IsZoom)
		{
			m_pBulletManager->Create({ m_ObjPos.x, (m_LookatPos.y + m_CameraPos.y) / 2, m_ObjPos.z },
				m_CameraRotate,
				&vec);
		}
		else
		{
			m_pBulletManager->Create({ m_ObjPos.x, m_CameraPos.y - 25.f, m_ObjPos.z },
				m_CameraRotate,
				&vec);
		}
		m_FiringCount = 120;
	}
	else if (m_FiringCount > 0)
	{
		m_FiringCount--;
	}

	///////////////////////////////////////////////　ここまで　/////////////////////////////////////////////////////////

	BattleDataManager::Instance().SetPlayerToZoom(m_IsZoom);

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
	m_OldRotate = m_Rotate;

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

	if (!m_IsZoom)
	{
		if (nextLookatPos <= m_CameraPos.y + 100.f && nextLookatPos >= m_CameraPos.y - 25.f)							//!<	100, 25	目で見て決めたカメラの上限と下限
		{
			m_LookatPos.y = nextLookatPos;
		}
	}
	else
	{
		if (nextLookatPos <= m_CameraPos.y + 100.f && nextLookatPos >= m_CameraPos.y)							//!<	100, 25	目で見て決めたカメラの上限と下限
		{
			m_LookatPos.y = nextLookatPos;
		}
		if (m_LookatPos.y < m_CameraPos.y)
		{
			m_LookatPos.y = m_CameraPos.y;
		}
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
	if (m_IsFpsMode)
	{
		m_CameraPos = m_CameraPos + vecAxisZ * 50.f;////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_LookatPos = m_LookatPos + vecAxisZ * 50.f;////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//		味方
//
//----------------------------------------------------------------------------------------------------------------------
void Cruiser::ControlAlly()
{
	m_pStateMachine->Update();
}

//----------------------------------------------------------------------------------------------------------------------
//
//		敵
//
//----------------------------------------------------------------------------------------------------------------------
void Cruiser::ControlEnemy()
{
	m_pStateMachine->Update();
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

