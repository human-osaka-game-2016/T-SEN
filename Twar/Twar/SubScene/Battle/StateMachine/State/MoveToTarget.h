//==================================================================================================================================//
//!< @file		MoveToTarget.h
//!< @brief		MoveToTargetクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef MOVE_TO_TARGET_H
#define MOVE_TO_TARGET_H

#include "State.h"
#include "../../Ship/Ship.h"

class MoveToTarget : public State<Ship>
{

public:
	/**インスタンスを生成する関数*/
	static void Create()
	{
		if(m_pMoveToTarget == nullptr)
		{
			m_pMoveToTarget = new MoveToTarget();
		}
	}

	/**
	* 実体を取得する関数
	* @return  MoveToTargetクラスのインスタンスへのポインタ
	*/
	static MoveToTarget* Instance(){ return m_pMoveToTarget; }

	/**インスタンスを破棄する関数*/
	static void Delete()
	{
		delete m_pMoveToTarget;
		m_pMoveToTarget = nullptr;
	}

	/**
	* 開始関数
	* @param pShip	Shipクラスのインスタンスへのポインタ
	*/
	virtual void Enter(Ship* pShip)override;

	/**
	* 実行関数
	* @param pShip	Shipクラスのインスタンスへのポインタ
	*/
	virtual void Execute(Ship* pShip)override;

	/**
	* 終了関数
	* @param pShip	Shipクラスのインスタンスへのポインタ
	*/
	virtual void Exit(Ship* pShip)override;

private:
	static MoveToTarget*		m_pMoveToTarget;	// MoveToTargetクラスのインスタンスへのポインタ

	/**Constrctor*/
	MoveToTarget(){}

	/**Destrctor*/
	virtual ~MoveToTarget(){}

};

#endif	// MOVE_TO_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
