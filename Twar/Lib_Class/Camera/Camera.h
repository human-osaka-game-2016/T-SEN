/**
* @file  Camera.h
* @brief カメラクラス
* @author haga
*/
#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>

/**
* カメラクラス.
*/
class Camera
{
private:
	LPDIRECT3DDEVICE9		m_pD3Device;		//!< Direct3Dのデバイス
	float					m_windowWidth;		//!< ウィンドウサイズ幅
	float					m_windowHeight;		//!< ウィンドウサイズ高さ

public:
	/**コンストラクタ*/
	Camera(LPDIRECT3DDEVICE9 pD3Device);
	/**デストラクタ*/
	~Camera();

	/**
	* ウインドウの幅と高さを取得す る関数<br>
	* @param[in] wWidth ウィンドウの幅
	* @param[in] wHeight ウィンドウの高さ
	*/
	void InitWindowsize(float wWidth, float wHeight);

	/**
	* 視点座標変換と射影座標変換を行う関数.
	* @param[in] vEyePt			カメラの位置
	* @param[in] vLookatPt	    注視点
	* @param[in] angle			視野角
	*/
	void LookInCamera(const D3DXVECTOR3* vEyePt, const D3DXVECTOR3* vLookatPt, const float* angle);

};

#endif // CAMERA_H