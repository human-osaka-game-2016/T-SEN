/**
@file Ship.h
@brief Shipクラスヘッダ
@author kawaguchi
*/

#ifndef SHIP_H
#define	SHIP_H

#include <d3dx9.h>
//#include "ShipManager.h"
#include "../StateMachine/StateMachine.h"

class FbxModel;
class CameraController;
class GameLib;
class ShipManager;

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

	enum SHIP_ID						//!<	船の艦種を識別するID
	{
		BATTLESHIP,
		CRUISER,
		DESTROYER,

		NONE,
	};


	/**--@data 2017/02/04haga追加分----------------------------------------------------------------------------------------------------------*/

	/**-----Static variable----*/
	static const float			m_BattleShipSpeedLimit;			//!< 戦艦のスピード限界値
	static const float			m_CruiserSpeedLimit;			//!< 巡洋艦のスピード限界値
	static const float			m_DestroyerSpeedLimit;			//!< 駆逐艦のスピード限界値

	/**----haga追加分終了---------------------------------------------------------------------------------------------------------------------*/

	/**
	コンストラクタ
	@param	pos			オブジェクトの中心座標
	@param	status		ステータス
	*/
	Ship(D3DXVECTOR3* pos, STATUS status, SHIP_ID ShipID);

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

	/**--@data 2017/02/04haga追加分----------------------------------------------------------------------------------------------------------*/
	/**-----Getter-------------*/
	const D3DXVECTOR3&  GetObjPos() { return m_ObjPos; }
	float				GetRotate() { return m_Rotate; }
	float				GetSpeedLimit(){ return m_SpeedLimit; }
	float				GetOldRotate() { return m_OldRotate; }
	StateMachine<Ship>*	GetStateMachine()const{ return m_pStateMachine; }
	const D3DXVECTOR3&	GetTargetPos(){ return m_TargetPos; }
	float				GetToTargetAngle(){ return m_TargetAngle; }
	int					GetBulletIntervalCount(){ return m_BulletIntervalCount; }
	bool				GetIsHit(){ return m_IsHit; }
	int					GetAvoidedTimeCount(){  return m_AvoidedTimeCount; }
	float				GetTurningSpeed(){ return m_TurningSpeed; }
	int					GetTurningTimeCount(){ return m_TurningTimeCount; }
	int					GetPlayerAttackedCount(){ return m_PlayerAttackedCount; }

	/**-----Setter-------------*/
	void SetObjPos(const D3DXVECTOR3& pos){ m_ObjPos = pos; }
	void SetRotate(float rotate){ m_Rotate = rotate; }
	void SetOldRotate(float rotate){ m_OldRotate = rotate; }
	void SetTargetPos(const D3DXVECTOR3& targetPos){ m_TargetPos = targetPos; }
	void SetTargetAngle(float angle){ m_TargetAngle = angle; }
	void SetBulletIntervalCount(int bulletInterval){ m_BulletIntervalCount = bulletInterval; }
	void SetIsHit(bool isHit){ m_IsHit = isHit; }
	void SetAvoidedTimeCount(int avoidedTimeCount){ m_AvoidedTimeCount = avoidedTimeCount; }
	void SetRotaion(const D3DXMATRIX& matRotation){ m_Rotation = matRotation; }
	void SetTurningSpeed(float turningSpeed){ m_TurningSpeed = turningSpeed; }
	void SetTurningTimeCount(int timeCount){ m_TurningTimeCount = timeCount; }

	/**--haga追加分終了--------------------------------------------------------------------------------------------------------------------*/

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
	int	m_ShipID;
	ATTR					m_Attr;					//!<	Shipの属性
	STATUS					m_Status;				//!<	ステータス

	/**
	船体の回転関係
	*/
	D3DXMATRIX				m_Rotation;
	float					m_Rotate;
	float m_OldRotate;

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
	static const float		m_PitchSpeed;
	static const float		m_PitchUpperLimit;
	static const float		m_PitchLowerLimit;

	/**
	船体の速度関係
	*/
	static const float		m_LimitArrivalFlame;	//!<	限界速度到達フレーム
	static const float		m_DecelerationSpeed;	//!<	減速スピード
	float					m_SpeedLimit;			//!<	限界スピード値 2017/02/05haga追加分

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

	bool				m_IsHit;
	bool				m_IsRush;

	/**--@data 2017/02/04追加 haga--------------------------------------------------------------------------------------------------*/

	StateMachine<Ship>*		m_pStateMachine;			//!< StateMachineクラスのインスタンスへのポインタ
	D3DXVECTOR3				m_TargetPos;				//!< ターゲットの位置座標
	float					m_TargetAngle;				//!< ターゲットへの角度
	float					m_TurningSpeed;				//!< 旋回するときのスピード
	int						m_TurningTimeCount;			//!< 旋回時間カウント
	int						m_BulletIntervalCount;		//!< 弾の発射間隔のカウント数
	int						m_AvoidedTimeCount;			//!< 回避時間をカウントする変数
	int						m_PlayerAttackedCount;		//!< プレイヤーに攻撃された回数

	/**--haga追加分終了-------------------------------------------------------------------------------------------------------------*/

	/**	case Control of "the player" */
	virtual void ControlPlayer() = 0;

	/**	case Control of "the ally" */
	virtual void ControlAlly() = 0;

	/**	case Control of "the enemy" */
	virtual void ControlEnemy() = 0;
};

#endif	//	SHIP_H
