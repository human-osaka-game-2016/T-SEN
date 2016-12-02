/**
* @file		Camera.cpp
* @brief	Cameraクラス実装
* @author	haga
*/
#include "Camera.h"

namespace{

const float defaultNearZ = 1.0f;		// 最近点のデフォルト値
const float defaultFarZ = 1000.f;		// 最遠点のデフォルト値

}

Camera::Camera(LPDIRECT3DDEVICE9 pD3Device) 
	: m_pD3Device(pD3Device)
	, m_WindowWidth(0)
	, m_WindowHeight(0)
	, m_NearZ(defaultNearZ)
	, m_FarZ(defaultFarZ)
{
}

Camera::~Camera()
{
}

// ウインドウの幅と高さを取得する関数
void Camera::InitWindowSize(float winWidth, float winHeight)
{
	m_WindowWidth = winWidth;
	m_WindowHeight = winHeight;
}

// 最近点の値をセットする関数
void Camera::SetNearZ(float nearZ)
{
	m_NearZ = nearZ;
}

// 最遠点の値をセットする関数
void Camera::SetFarZ(float farZ)
{
	m_FarZ = farZ;
}

// 視点座標変換と射影座標変換を行う関数
void Camera::LookInCamera(const D3DXVECTOR3* vEyePt, const D3DXVECTOR3* vLookatPt, const float* angle)
{
	// 視点座標
	D3DXMATRIX    matView;						  // 変換後の視点座標を格納する行列
	D3DXVECTOR3   vUpVec = { 0.0f, 1.0f, 0.0f };  // カメラの上方向のベクトル。ここは固定
	D3DXMatrixLookAtLH(&matView, vEyePt, vLookatPt, &vUpVec);
	m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	// 射影座標
	D3DXMATRIX matProj;							   // 変換後の射影座標を格納する行列
	float viewAngle = D3DXToRadian(*angle);		   // 視野角
	float aspect = m_WindowWidth / m_WindowHeight; // アスペクト比(画面(ウィンドウ)サイズによって変更)
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, m_NearZ, m_FarZ);
	m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);
}
