//==================================================================================================================================//
//!< @file		SearchTarget.h
//!< @brief		SearchTargetクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef SEARCH_TARGET_H
#define SEARCH_TARGET_H

#include "State.h"
#include "../../Ship/Ship.h"

class SearchTarget : public State<Ship>
{

public:
	/**Constructor*/
	SearchTarget();

	/**Destructor*/
	~SearchTarget();

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
	* 終了関数
	* @param pShip	Shipクラスのインスタンスへのポインタ
	*/
	virtual void Exit(Ship* pShip)override;

};

#endif	// SEARCH_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
