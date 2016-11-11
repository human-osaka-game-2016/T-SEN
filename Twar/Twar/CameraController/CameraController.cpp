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
m_vEyePt(0.0f,50.0f,0.0f),
m_vLookPt(0.0f, 10.0f, -5.0f),
m_angle(50.f)
{
}

// デストラクタ
CameraController::~CameraController()
{
	delete m_pInputKey;
	delete m_pCamera;
}

// コントロール関数
void CameraController::Control()
{
	m_pCamera->InitWindowsize(1600.f, 900.f);

	if (GameLib::GetInstance().CheckKey(DIK_W, W) == ON)
	{
		m_vEyePt.y -= 0.5f;
	}
	if (GameLib::GetInstance().CheckKey(DIK_S, S) == ON)
	{
		m_vEyePt.y += 0.5f;
	}
	if (GameLib::GetInstance().CheckKey(DIK_D, D) == ON)
	{
		m_vEyePt.x -= 0.5f;
	}
	if (GameLib::GetInstance().CheckKey(DIK_A, A) == ON)
	{
		m_vEyePt.x += 0.5f;
	}


}

// 座標変換関数
void CameraController::TransformView(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookPt, float angle)
{
	m_pCamera->LookInCamera(&vEyePt,&vLookPt,&angle);
}