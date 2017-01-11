/**
* @file		StateMachine.h
* @brief	StateMachineクラスヘッダ
* @author	haga
*/

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"

class StateMachine
{

public:

	StateMachine(const D3DXVECTOR3& rPos, float angle, float slant, float speedLimit);

	~StateMachine();

	/**更新関数*/
	void Update();

	/**データセット関数*/
	void SetStatus(const Ship::STATUS& rStatus);

	/**データ取得関数群*/
	const D3DXVECTOR3&	GetPos() { return m_Pos; }
	float				GetAngle(){ return m_Angle; }
	float				GetSlant(){ return m_Slant; }
	const Ship::STATUS&	GetStatus(){ return m_Status; }

private: 

	// 遷移ステップ
	enum STEP
	{
		ENTER,		//!< 選んでいるステイトになる 
		EXECUTE,	//!< 選んだステイトを実行する
		EXIT,		//!< 選んでいるステイトをやめる
		
	};

	State*				m_pState;			//!< Stateクラスの継承クラスのインスタンスへのポインタ
	STEP				m_Step;				//!< Stateクラスの遷移ステップ
	State::STATE_ID		m_CurrentStateID;	//!< 現在のStateID
	State::STATE_ID		m_NextStateID;		//!< 次のStateID

	D3DXVECTOR3			m_Pos;				//!< 位置情報
	float				m_Angle;			//!< 角度
	float				m_Slant;			//!< 船の傾き
	Ship::STATUS		m_Status;			//!< ステータス
	const float			m_SpeedLimit;		//!< スピードの限界値

};

#endif	// STATE_MACHINE_H
