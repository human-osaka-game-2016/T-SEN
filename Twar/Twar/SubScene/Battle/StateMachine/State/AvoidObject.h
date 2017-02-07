//==================================================================================================================================//
//!< @file		AvoidObject.h
//!< @brief		AvoidObjectクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef AVOID_OBJECT_H
#define AVOID_OBJECT_H

#include "../../Ship/Ship.h"
#include "State.h"

/**
* 回避状態
* 衝突などが起きた場合に遷移する状態
*/
class AvoidObject : public State<Ship>
{

public:
	/**インスタンスを生成する関数*/
	static void Create()
	{
		if(m_pAvoidObject == nullptr)
		{
			m_pAvoidObject = new AvoidObject();
		}
	}

	/**
	* 実体を取得する関数
	* @return  mAvoidObjectクラスのインスタンスへのポインタ
	*/
	static AvoidObject* Instance(){ return m_pAvoidObject; }

	/**インスタンスを破棄する関数*/
	static void Delete()
	{
		delete m_pAvoidObject;
		m_pAvoidObject = nullptr;
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
	static AvoidObject*		m_pAvoidObject;		//!< AvoidObjectクラスのインスンタンスへのポインタ

	/**Constructor*/
	AvoidObject(){}

	/**Desutructor*/
	~AvoidObject(){}

};

#endif	// AVOID_OBJECT_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
