/**
	@file ShipManager.h
	@brief ShipManagerクラスヘッダ
	@author kawaguchi
*/

#ifndef SHIP_H
#define	SHIP_H

#include <d3dx9.h>

class FbxModel;
class CameraController;
class GameLib;
class Collision;
class StateMachine;

/**
	Ship全体の親クラス
*/
class Ship
{
	friend class ShipManager;

public:
	/**
		ステータス
	*/
	typedef struct STATUS
	{
		int m_Hp;
		float m_Speed;
	};

	/**
		コンストラクタ
		@param	pos			オブジェクトの中心座標
		@param	status		ステータス
	*/
	Ship(D3DXVECTOR3* pos, STATUS status);

	/**	デストラクタ */
	virtual ~Ship();

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

	bool Zoom(){ return m_IsZoom; }

protected:
	/**
		Shipの属性
	*/
	enum ATTR
	{
		PLAYER,
		ALLY,
		ENEMY
	};

	GameLib&				m_pGameLib;				//!<	GameLib
	FbxModel*				m_pFbx;					//!<	モデルデータ
	D3DXVECTOR3		        m_ObjPos;				//!<	座標
	CameraController&		m_pcameraController;	//!<	カメラコントローラー
	
	ATTR					m_Attr;					//!<	Shipの属性
	STATUS					m_Status;				//!<	ステータス

	/**
		船体の回転関係
	*/
	D3DXMATRIX				m_Rotation;
	float					m_Rotate;

	/**
		船体の傾き関係
	*/
	D3DXMATRIX				m_Slope;
	float					m_Slant;
	bool					m_IsRightSlantLimit;
	bool					m_IsLeftSlantLimit;

	/**
		船体の揺れ関係
	*/
	bool					m_IsUp;
	float					m_PitchSpeed;
	float					m_PitchUpperLimit;
	float					m_PitchLowerLimit;

	/**
		船体の速度関係
	*/
	static const float		m_LimitArrivalFlame;	//!<	限界速度到達フレーム
	static const float		m_DecelerationSpeed;	//!<	減速スピード

	/**
	カメラの関係
	*/
	static const float		m_CameraHeight;
	D3DXMATRIX				m_CameraRotation;
	float					m_CameraRotate;
	D3DXVECTOR3				m_CameraPos;
	D3DXVECTOR3				m_LookatPos;
	float					m_Angle;
	bool					m_IsZoom;
	static const float		m_NormalAngle;
	static const float		m_ZoomAngle;


	Collision*		m_pCollision;
	StateMachine*	m_pStateMachine;

	/**	case Control of "the player" */
	virtual void ControlPlayer() = 0;
	
	/**	case Control of "the ally" */
	virtual void ControlAlly() = 0;
	
	/**	case Control of "the enemy" */
	virtual void ControlEnemy() = 0;
};

#endif	//	SHIP_H
