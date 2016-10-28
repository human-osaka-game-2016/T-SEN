/**
* @file  Camera.cpp
* @brief カメラクラス
* @author haga
*/
#include "Camera.h"

Camera::Camera(LPDIRECT3DDEVICE9 pD3Device) :
m_pD3Device(pD3Device),
m_windowWidth(0),
m_windowHeight(0)
{
}

Camera::~Camera()
{
}



// ウインドウの幅と高さを取得する関数<br>
void Camera::InitWindowsize(float wWidth, float wHeight)
{
	m_windowWidth = wWidth;
	m_windowHeight = wHeight;
}

// 視点座標変換と射影座標変換を行う関数(数値は仮置き)
void Camera::LookInCamera(const D3DXVECTOR3* vEyePt, const D3DXVECTOR3* vLookatPt, const float* angle)
{
	// 視点座標
	D3DXMATRIX    matView;						  // 変換後の視点座標を格納する行列
	D3DXVECTOR3   vUpVec = { 0.0f, 1.0f, 0.0f };  // カメラの上方向のベクトル
	D3DXMatrixLookAtLH(&matView, vEyePt, vLookatPt, &vUpVec);
	m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	// 射影座標
	D3DXMATRIX matProj;							   // 変換後の射影座標を格納する行列
	float viewAngle = D3DXToRadian(*angle);		   // 視野角
	float aspect = m_windowWidth / m_windowHeight; // アスペクト比(画面サイズによって変更)
	float nearZ = 1.0f;							   // 最近点
	float farZ = 10000.f;						   // 最遠点
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);
	m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);
}