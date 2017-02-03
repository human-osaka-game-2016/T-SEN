//==================================================================================================================================//
//!< @file		AttackTarget.h
//!< @brief		AttackTargetクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef ATTACK_TARGET_H
#define ATTACK_TARGET_H

#include "State.h"
#include "../../Ship/Ship.h"

/**
* ターゲットへ攻撃を行う状態
*/
class AttackTarget : public State<Ship>
{

public:
	/**インスタンスを生成する関数*/
	static void Create()
	{
		if(m_pAttackTarget == nullptr)
		{
			m_pAttackTarget = new AttackTarget();
		}
	}

	/**
	* 実体を取得する関数
	* @return  AttackTargetクラスのインスタンスへのポインタ
	*/
	static AttackTarget* Instance(){ return m_pAttackTarget; }

	/**インスタンスを破棄する関数*/
	static void Delete()
	{
		delete m_pAttackTarget;
		m_pAttackTarget = nullptr;
	}

	/**
	* 開始処理
	* @param pShip	Shipクラスのインスタンスへのポインタ
	*/
	virtual void Enter(Ship* pShip)override;

	/**
	* 実行関数
	* @param pShip	Shipクラスのインスタンスへのポインタ
	*/
	virtual void Execute(Ship* pShip)override;

	/**
	* 終了処理
	* @param pShip	Shipクラスのインスタンスへのポインタ
	*/
	virtual void Exit(Ship* pShip)override;

private:
	static AttackTarget*	  m_pAttackTarget;		//!< AttackTargetクラスのインスタンスへのポインタ

	/**Constructor*/
	AttackTarget(){}

	/**Destructor*/
	virtual ~AttackTarget(){}

};

#endif // ATTACK_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
