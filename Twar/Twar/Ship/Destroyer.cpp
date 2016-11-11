#include "Destroyer.h"


Destroyer::Destroyer(D3DXVECTOR3* pos):
Ship(pos)
{
}


Destroyer::~Destroyer()
{
}


void Destroyer::Control()
{
	switch (m_Attr)
	{
	case Ship::PLAYER:
		Destroyer::Player();
		break;

	case Ship::ALLY:
		Destroyer::Ally();
		break;

	case Ship::ENEMY:
		Destroyer::Enemy();
		break;
	}
}

void Destroyer::Player()
{
	D3DXVECTOR3 vecAxisX{ 1.f, 0.f, 0.f };
	D3DXVECTOR3 vecAxisZ{ 0.f, 0.f, 1.f };
	static bool frag = false;

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


	//	if (m_mouse.GetIsLAction())
	//	{
	//		D3DXVECTOR2 mousePos;
	//		D3DXVECTOR3 mousePos3D;
	//		mousePos.x = static_cast<float>(m_mouse.GetPosX());
	//		mousePos.y = static_cast<float>(m_mouse.GetPosY());
	//		m_clickPosConverter.Convert3DMousePos(&mousePos3D, mousePos);
	//
	//		m_objPos = mousePos3D;
	//	}
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
	if (m_InputKey.m_Key[UP] == BTN_ON)
	{
		m_ObjPos += vecAxisZ * 1.f;
	}
	if (m_InputKey.m_Key[DOWN] == BTN_ON)
	{
		m_ObjPos -= vecAxisZ * 1.f;
	}
	//	}
	if (m_InputKey.m_Key[LEFT] == BTN_ON)
	{
		m_Rotate -= 1;
		frag = false;
	}
	if (m_InputKey.m_Key[RIGHT] == BTN_ON)
	{
		m_Rotate += 1;
		frag = false;
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

}

void Destroyer::Ally()
{
}

void Destroyer::Enemy()
{
}

void Destroyer::Draw()
{
	D3DXMatrixRotationY(&m_Rotation, m_Rotate * 3.141592f / 360.f);
	TransWorld();		// ƒ[ƒ‹ƒhÀ•W•ÏŠ·
//	m_pcameraController->TransformView();
	m_pFbx->DrawFbx();
}
