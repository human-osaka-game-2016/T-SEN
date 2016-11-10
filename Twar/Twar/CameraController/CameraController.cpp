/**
* @file   CameraController.cpp
* @brief  カメラコントローラークラスのcpp
* @author haga
*/

#include "CameraController.h"
#include "GameLib/GameLib.h"
#include "Camera/Camera.h"

// コンストラクタ
CameraController::CameraController():
m_pCamera(new Camera(GameLib::GetInstance().GetDevice())),
m_pInputKey(new InputKey()),
m_vEyePt(0.0f,10.0f,-5.0f),
m_vLookPt(0.0f, 0.0f, 0.0f),
m_angle(50.f)
{
}

// デストラクタ
CameraController::~CameraController()
{
	delete m_pCamera;
}

// コントロール関数
void CameraController::Control()
{
	m_pCamera->InitWindowsize(1280.f, 720.f);
	GameLib::GetInstance().UpDateDI();
	GameLib::GetInstance().CheckKey(m_pInputKey->m_diks[DIK_W], W);
	GameLib::GetInstance().CheckKey(m_pInputKey->m_diks[DIK_S], S);
	GameLib::GetInstance().CheckKey(m_pInputKey->m_diks[DIK_D], D);
	GameLib::GetInstance().CheckKey(m_pInputKey->m_diks[DIK_A], A);
	GameLib::GetInstance().CheckKey(m_pInputKey->m_diks[DIK_Z], Z);
	GameLib::GetInstance().CheckKey(m_pInputKey->m_diks[DIK_X], X);

	if (m_pInputKey->m_Key[W] == ON)
	{
		m_vEyePt.y += 0.1f;
	}
	if (m_pInputKey->m_Key[S] == ON)
	{
		m_vEyePt.y -= 0.1f;
	}
	if (m_pInputKey->m_Key[D] == ON)
	{
		m_vEyePt.x += 0.2f;
	}
	if (m_pInputKey->m_Key[A] == ON)
	{
		m_vEyePt.x -= 0.2f;
	}
	if (m_pInputKey->m_Key[Z] == ON)
	{
		if (m_angle <= 90.f)
		{
			m_angle += 0.1f;
		}
	}
	if (m_pInputKey->m_Key[X] == ON)
	{
		if (m_angle >= 0.f)
		{
			m_angle -= 0.1f;
		}
	}

}

// 座標変換関数
void CameraController::TransformView()
{
	m_pCamera->LookInCamera(&m_vEyePt,&m_vLookPt,&m_angle);
}