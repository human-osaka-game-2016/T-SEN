//==================================================================================================================================//
//!< @file		TurningAround.h
//!< @brief		TurningAroundクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef TURNING_AROUND_H
#define TURNING_AROUND_H

#include "State.h"
#include "../../Ship/Ship.h"

class TurningAround : public State<Ship>
{

public:
	/**Constructor*/
	TurningAround();

	/**Destructor*/
	~TurningAround();

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

#endif	// TURNING_AROUND_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
