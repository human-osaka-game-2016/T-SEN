/**
	@file ShipManager.h
	@brief ShipManagerクラスヘッダ
	@author kawaguchi
*/
#ifndef SHIP_H
#define	SHIP_H

#include "Fbx/FbxRelated.h"
#include "../CameraController/CameraController.h"
#include "GameLib/Lib/GraphicsDevice.h"
#include "GameLib/Lib/InputKey.h"
#include "GameLib/Lib/InputMouse.h"
#include "GameLib/GameLib.h"

/**
	Ship全体の親クラス
*/
class Ship
{
	friend class ShipManager;

protected:
	/**
		ステータス
	*/
	typedef struct STATUS
	{
		int m_Hp;
		float m_Speed;
	};

	/**
		Shipの属性
	*/
	enum ATTR
	{
		PLAYER,
		ALLY,
		ENEMY
	};

	IDirect3DDevice9*		m_pD3Device;			//!<	Direct3Dのデバイス
	D3DXVECTOR3		        m_ObjPos;				//!<	座標
	CameraController*		m_pcameraController;	//!<	カメラコントローラー
	InputKey				m_InputKey;				//!<	コントロールキー
	InputMouse				m_Mouse;				//!<	マウス
	FbxModel*				m_pFbx;					//!<	モデルデータ
	
	ATTR					m_Attr;					//!<	Shipの属性
	STATUS					m_Status;				//!<	ステータス

	/**
		船体の回転関係
	*/
	D3DXMATRIX				m_Rotation;
	float					m_Rotate;
	float					m_RotateSpeed;

	/**
		船体の傾き関係
	*/
	D3DXMATRIX				m_Slope;
	float					m_Slant;
	bool					m_IsRightSlantLimit;
	bool					m_IsLeftSlantLimit;

	/**
		カメラの回転関係
	*/
	D3DXMATRIX				m_CameraRotation;
	float					m_CameraRotate;
	D3DXVECTOR3				m_CameraPos;
	D3DXVECTOR3				m_LookatPos;
	float					m_Angle;
	bool					m_IsZoom;

	const float				m_DecelerationSpeed = 0.002f;	//!<	減速スピード

	/**	case Control of "the player" */
	virtual void ControlPlayer() = 0;
	
	/**	case Control of "the ally" */
	virtual void ControlAlly() = 0;
	
	/**	case Control of "the enemy" */
	virtual void ControlEnemy() = 0;

private:

	

public:
	/**
		コンストラクタ
		@param	pos			オブジェクトの中心座標
		@param	status		ステータス
	*/
	Ship(D3DXVECTOR3* pos, STATUS status);

	/**	デストラクタ */
	~Ship();

	/**	描画関数 */
	virtual void Draw();
	
	/**	コントロール関数 */
	virtual void Control();
	
	/**	ワールド座標変換関数 */
	void TransWorld();
	
	/**
		カメラ座標と注視点を決める関数
		@param	radius		カメラ座標と注視点の中点
	*/
	void CameraTransWorld(float radius);

};

#endif	//	SHIP_H