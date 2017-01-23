/**
* @file   CameraController.h
* @brief  CameraControllerクラスヘッダ
* @author kawaguchi
*/

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <d3dx9.h>

class Camera;

/**
* カメラのコントローラークラス
*/
class CameraController
{
public:
	/**
	* Singletonパターン<br>
	* 実体をつくる関数.
	*/
	static CameraController &GetInstance()
	{
		static CameraController m_cameraController;

		return m_cameraController;
	}

	/**
	* 座標変換関数.
	* @param vEyePt		カメラの位置
	* @param vLookPt	注視点
	* @param angle		視野角
	*/
	void TransformView(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookPt, float angle);

	/**デストラクタ*/
	~CameraController();

private:
	/**
	* コンストラクタ.
	* Singletonパターンの為private
	*/
	CameraController();

	Camera*		m_pCamera;			//!< Cameraクラスのインスタンスへのポインタ
};

#endif	// CAMERA_CONTROLLER_H
