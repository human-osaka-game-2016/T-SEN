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
	/**Constrctor*/
	MoveToTarget();

	/**Destrctor*/
	~MoveToTarget();

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

};

#endif	// MOVE_TO_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
