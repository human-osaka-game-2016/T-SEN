/**
* @file   CameraController.cpp
* @brief  CameraControllerクラス実装
* @author kawaguchi
*/

#include "CameraController.h"
#include "GameLib/GameLib.h"
#include "Camera/Camera.h"

// コンストラクタ
CameraController::CameraController()
	: m_pCamera(new Camera(GameLib::Instance().GetDevice()))
{
	// アスペクト比の設定
	float winWidth = static_cast<float>(GameLib::Instance().GetWindowWidth());
	float winHeight = static_cast<float>(GameLib::Instance().GetWindowHeight());
	m_pCamera->InitWindowSize(winWidth, winHeight);

	// 最遠点の設定
	float farZ = 10000.f;
	m_pCamera->SetFarZ(farZ);
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

