#include "Cruiser.h"


Cruiser::Cruiser(D3DXVECTOR3* pos):
Ship(pos)
{
}


Cruiser::~Cruiser()
{
}


void Cruiser::Control()
{
	switch (m_Attr)
	{
	case Ship::PLAYER:
		Cruiser::Player();
		break;

	case Ship::ALLY:
		Cruiser::Ally();
		break;

	case Ship::ENEMY:
		Cruiser::Enemy();
		break;
	}
}

void Cruiser::Player()
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

void Cruiser::Ally()
{
}

void Cruiser::Enemy()
{
}

void Cruiser::Draw()
{
	D3DXMatrixRotationY(&m_Rotation, m_Rotate * 3.141592f / 360.f);
	TransWorld(&m_ObjPos, &m_Rotation);		// ���[���h���W�ϊ�
//	m_pcameraController->TransformView();
	m_pFbx->DrawFbx();
}