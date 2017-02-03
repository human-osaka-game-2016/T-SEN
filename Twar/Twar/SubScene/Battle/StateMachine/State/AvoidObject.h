//==================================================================================================================================//
//!< @file		AvoidObject.h
//!< @brief		AvoidObjectクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef AVOID_OBJECT_H
#define AVOID_OBJECT_H

#include "../../Ship/Ship.h"
#include "State.h"

class AvoidObject : public State<Ship>
{

public:
	/**Constructor*/
	AvoidObject();

	/**Desutructor*/
	~AvoidObject();

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

#endif	// AVOID_OBJECT_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
