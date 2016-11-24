/**
	@file   CameraController.h
	@brief  カメラコントローラークラスのh
	@author kawaguchi
*/
#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <d3dx9.h>

class Camera;

/**
* カメラコントローラークラスのh
*/
class CameraController
{
private:
	Camera*		m_pCamera;			//!< カメラ

public:
	/**コンストラクタ*/
	CameraController();
	/**デストラクタ*/
	~CameraController();

	// 実体をつくる
	static CameraController &GetInstance()
	{
		static CameraController m_cameraController;

		return m_cameraController;
	}

	/**
	* 座標変換関数
	*/
	void TransformView(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookPt, float angle);
};

#endif	// CAMERA_CONTROLLER_H
