//==================================================================================================================================//
//!< @file		TurningAround.h
//!< @brief		TurningAroundクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef TURNING_AROUND_H
#define TURNING_AROUND_H

#include "State.h"
#include "../../Ship/Ship.h"

/**
* 旋回する状態
*/
class TurningAround : public State<Ship>
{

public:
	/**インスタンスを生成する関数*/
	static void Create()
	{
		if(m_pTurningAround == nullptr)
		{
			m_pTurningAround = new TurningAround();
		}
	}

	/**
	* インスタンスを取得する関数
	* @return  MoveToTargetクラスのインスタンスへのポインタ
	*/
	static TurningAround* Instance(){ return m_pTurningAround; }

	/**インスタンスを破棄する関数*/
	static void Delete()
	{
		delete m_pTurningAround;
		m_pTurningAround = nullptr;
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
	static	TurningAround*			m_pTurningAround;		//!< TurningAroundクラスのインスタンスへのポインタ

	/**Constructor*/
	TurningAround(){}

	/**Destructor*/
	~TurningAround(){}

};

#endif	// TURNING_AROUND_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
