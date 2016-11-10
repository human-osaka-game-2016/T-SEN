/**
* @file   CameraController.h
* @brief  カメラコントローラークラスのh
* @author haga
*/
#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <d3dx9.h>

class Camera;
class InputKey;

/**
* カメラコントローラークラスのh
*/
class CameraController
{
private:
	D3DXVECTOR3 m_vEyePt;			//!< カメラの位置
	D3DXVECTOR3 m_vLookPt;			//!< カメラの注視点
	float		m_angle;			//!< カメラの倍率
	Camera*		m_pCamera;			//!< カメラ
	InputKey*    m_pInputKey;         //!< コントロールキー

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
	* コントロール関数
	*/
	void Control();

	/**
	* 座標変換関数
	*/
	void TransformView(D3DXVECTOR3 vLookPt);

	/**
	* ゲッター関数
	*/
	D3DXVECTOR3 GetEyePos(){ return m_vEyePt; }
	D3DXVECTOR3 GetLookAtPos(){ return m_vLookPt; }
	float GetAngle(){ return m_angle; }

};

#endif	// CAMERA_CONTROLLER_H
