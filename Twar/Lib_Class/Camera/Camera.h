/**
* @file		Camera.h
* @brief	Cameraクラスヘッダ 
* @author	haga
*/
#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>

/**
* DirectXのカメラクラス.
*/
class Camera
{
private:
	LPDIRECT3DDEVICE9		m_pD3Device;		//!< Direct3Dのデバイス
	float					m_WindowWidth;		//!< ウィンドウサイズ横幅
	float					m_WindowHeight;		//!< ウィンドウサイズ縦幅
	float					m_NearZ;			//!< 最近点
	float					m_FarZ;				//!< 最遠点

public:
	/**コンストラクタ*/
	Camera(LPDIRECT3DDEVICE9 pD3Device);

	/**デストラクタ*/
	~Camera();

	/**
	* ウインドウの幅と高さを取得する関数.
	* @param[in] winWidth	ウィンドウの幅
	* @param[in] winHeight	ウィンドウの高さ
	*/
	void InitWindowSize(float winWidth, float winHeight);

	/**
	* 最近点の値を設定する関数.
	* @param[in] nearZ	設定したい最近点
	*/
	void SetNearZ(float nearZ);

	/**
	* 最遠点の値を設定する関数.
	* @param[in] farZ	設定したい最遠点
	*/
	void SetFarZ(float farZ);

	/**
	* 視点座標変換と射影座標変換を行う関数.
	* @param[in] vEyePt			カメラの位置
	* @param[in] vLookatPt	    注視点
	* @param[in] angle			視野角
	*/
	void LookInCamera(const D3DXVECTOR3* vEyePt, const D3DXVECTOR3* vLookatPt, const float* angle);

};

#endif // CAMERA_H
