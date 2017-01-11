/**
* @file		State.h
* @brief	Stateクラスヘッダ
* @author	haga
*/ 

#ifndef STATE_H
#define STATE_H

#include <d3dx9.h>
#include "../Ship.h"

/**
* 船の状態の基底クラス
*/
class State
{
public:
	enum STATE_ID
	{
		PURSUIT,	//!< 追跡行動
		EVADE,		//!< 逃避行動
		ATTACK,		//!< 攻撃行動
	};

	State();

	virtual ~State();

	/**コントロール関数*/
	virtual State::STATE_ID Control(const Ship::STATUS& rStatus) = 0;

	/**
	* 船のデータをセットする関数
	*/
	void SetShipData(const D3DXVECTOR3& rPos, float angle, float slant, float speedLimit);

	/**データ取得関数群*/
	const D3DXVECTOR3&	GetPos() { return m_Pos; }
	float				GetAngle(){ return m_Angle; }
	float				GetSlant(){ return m_Slant; }
	const Ship::STATUS&	GetStatus(){ return m_Status; }

protected:
	D3DXVECTOR3			m_Pos;					//!< 位置情報
	float				m_Angle;				//!< 角度
	float				m_Slant;				//!< 船の傾き
	Ship::STATUS		m_Status;				//!< ステータス
	float				m_SpeedLimit;			//!< スピード限界値

	static const float	m_FiringRange;			//!< 射程 
	static const float	m_CorrectionAngle;		//!< 補正角度

};

#endif	// STATE_H

