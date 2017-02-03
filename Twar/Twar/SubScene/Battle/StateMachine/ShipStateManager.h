//==================================================================================================================================//
//!< @file		ShipStateManager.h
//!< @brief		ShipStateManagerクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef SHIP_STATE_MANAGER_H
#define SHIP_STATE_MANAGER_H

#include "../Ship/Ship.h"
#include "State/State.h"

/**
* Stateクラスを管理するクラス
* モノステイトパターン
*/
class ShipStateManager
{

public:
	/**軍艦の状態ID*/
	enum SHIP_STATE_ID
	{
		ATTACK_TARGET,		//!< ターゲットへ攻撃する
		SEARCH_TARGET,		//!< ターゲットを探索する
		AVOID_OBJECT,		//!< 物体を回避する
		MOVE_TO_TARGET,		//!< ターゲットへ移動する
		TURNING_AROUND,		//!< 周囲を旋回する
	};

	/**Stateクラスの継承クラス群を作成する関数*/
	static void  CreateStates();

	/**Stateクラスの継承クラス群を作成する関数*/
	static void  DeleteStates();

	/**
	* Stateクラスの継承クラスのインスタンスへのポインタを取得する関数
	* @param id 取得したいStateのID
	*/
	static State<Ship>*	GetShipState(SHIP_STATE_ID id);

private:
	/**Constructor*/
	ShipStateManager() = default;

	/**Destructor*/
	~ShipStateManager() = default;
};

#endif	// SHIP_STATE_MANAGER_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
