/**
	@file   CameraController.cpp
	@brief  カメラコントローラークラスのcpp
	@author kawaguchi
*/

#include "CameraController.h"
#include "GameLib/GameLib.h"
#include "Camera/Camera.h"

// コンストラクタ
CameraController::CameraController():
m_pCamera(new Camera(GameLib::Instance().GetDevice()))
{
}

// デストラクタ
CameraController::~CameraController()
{
	delete m_pCamera;
}

// 座標変換関数
void CameraController::TransformView(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookPt, float angle)
{
	m_pCamera->LookInCamera(&vEyePt,&vLookPt,&angle);
}