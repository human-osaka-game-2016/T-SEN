//==================================================================================================================================//
//!< @file		AttackTarget.h
//!< @brief		AttackTargetクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef ATTACK_TARGET_H
#define ATTACK_TARGET_H

#include "State.h"
#include "../../Ship/Ship.h"

class BulletManager;

class AttackTarget : public State<Ship>
{

public:
	/**
	* 実体を取得する関数
	* @return  AttackTargetクラスのインスタンスへのポインタ
	*/
	static AttackTarget* Instance()
	{
		static AttackTarget state;
		return &state;
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

	/**Destructor*/
	virtual ~AttackTarget();

private:
	BulletManager*    m_pBulletManager;		//!< BulletManagerクラスのインスタンスへのポインタ

	/**Constructor*/
	AttackTarget();

};

#endif // ATTACK_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
