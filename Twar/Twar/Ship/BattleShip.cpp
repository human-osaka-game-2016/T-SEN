#include "GameLib/GameLib.h"
#include "BattleShip.h"


BattleShip::BattleShip(D3DXVECTOR3* pos):
Ship(pos)
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
		BattleShip::Player();
		break;

	case Ship::ALLY:
		BattleShip::Ally();
		break;

	case Ship::ENEMY:
		BattleShip::Enemy();
		break;
	}
}

void BattleShip::Player()
{
	D3DXVECTOR3 vecAxisX{ 1.f, 0.f, 0.f };
	D3DXVECTOR3 vecAxisZ{ 0.f, 0.f, 1.f };

	m_InputKey.UpdateKey();
	m_Mouse.UpdateMouse();
	m_InputKey.CheckKey(DIK_UP, UP);
	m_InputKey.CheckKey(DIK_DOWN, DOWN);
	m_InputKey.CheckKey(DIK_RIGHT, RIGHT);
	m_InputKey.CheckKey(DIK_LEFT, LEFT);

	m_InputKey.CheckKey(DIK_W, W);
	m_InputKey.CheckKey(DIK_S, S);
	m_InputKey.CheckKey(DIK_D, D);
	m_InputKey.CheckKey(DIK_A, A);

	D3DXVec3TransformCoord(&vecAxisX, &vecAxisX, &m_Rotation);
	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Rotation);


	if (GameLib::GetInstance().ChecKMouseR() == PUSH)
	{
		m_Angle = 10.f;
		m_Zoom = true;
//		D3DXVECTOR2 mousePos;
//		D3DXVECTOR3 mousePos3D;
//		mousePos.x = static_cast<float>(m_mouse.GetPosX());
//		mousePos.y = static_cast<float>(m_mouse.GetPosY());
//		m_clickPosConverter.Convert3DMousePos(&mousePos3D, mousePos);
//	
//		m_objPos = mousePos3D;
	}

	if(GameLib::GetInstance().ChecKMouseR() == OFF)
	{
		m_Angle = 50.f;
		m_Zoom = false;
	}
	//	else
	//	{
	//		if (m_inputKey.m_Key[LEFT] == BTN_ON)
	//		{
	//			m_objPos -= vecAxisX * 1.f;
	//		}
	//		if (m_inputKey.m_Key[RIGHT] == BTN_ON)
	//		{
	//			m_objPos += vecAxisX * 1.f;
	//		}
	if (m_InputKey.m_Key[W] == BTN_ON)
	{
		m_ObjPos += vecAxisZ * 1.f;
	}

	if (m_InputKey.m_Key[S] == BTN_ON)
	{
		m_ObjPos -= vecAxisZ * 1.f;
	}

	if (m_InputKey.m_Key[A] == BTN_ON)
	{
		m_Rotate -= 1;
	}
	if (m_InputKey.m_Key[D] == BTN_ON)
	{
		m_Rotate += 1;
	}

//	if (m_InputKey.m_Key[W] == BTN_ON)
//	{
//		m_ObjPos += vecAxisZ * 1.f;
//	}
//	if (m_InputKey.m_Key[S] == BTN_ON)
//	{
//		m_ObjPos -= vecAxisZ * 1.f;
//	}
//	//	}
//	if (m_InputKey.m_Key[A] == BTN_ON)
//	{
//		m_Rotate -= 1;
//		frag = false;
//	}
//	if (m_InputKey.m_Key[D] == BTN_ON)
//	{
//		m_Rotate += 1;
//		frag = false;
//	}

	if (m_InputKey.m_Key[UP] == BTN_ON && m_LookatPos.y <= 100.f)
	{
		m_LookatPos.y += 2.f;
	}

	if (m_InputKey.m_Key[DOWN] == BTN_ON && m_LookatPos.y >= -25.f)
	{
		m_LookatPos.y -= 2.f;
	}

	if (m_InputKey.m_Key[LEFT] == BTN_ON)
	{
		m_CameraRotate -= 1;
		
		if (m_InputKey.m_Key[D] == BTN_ON)
		{
			m_CameraRotate -= 0.5f;
		}
	}
	if (m_InputKey.m_Key[RIGHT] == BTN_ON)
	{
		m_CameraRotate += 1;

		if (m_InputKey.m_Key[A] == BTN_ON)
		{
			m_CameraRotate += 0.5f;
		}
	}

	m_CameraPos.x = m_LookatPos.x = m_ObjPos.x;
	m_CameraPos.z = m_LookatPos.z = m_ObjPos.z;
}

void BattleShip::Ally()
{
}

void BattleShip::Enemy()
{
}

void BattleShip::Draw()
{
	D3DXMatrixRotationY(&m_Rotation, m_Rotate * 3.141592f / 360.f);
	D3DXMatrixRotationY(&m_CameraRotation, (m_Rotate + m_CameraRotate) * 3.141592f / 360.f);
	//	CameraTransWorld(200.f);
	TransWorld();		// ƒ[ƒ‹ƒhÀ•W•ÏŠ·
	//	m_pcameraController->TransformView();
	if (!m_Zoom)
	{
		m_pFbx->DrawFbx();
	}
}
