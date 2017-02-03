//==================================================================================================================================//
//!< @file		StateMachine.h
//!< @brief		StateMachineクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <windows.h>
#include "State/State.h"

/**
* ステートマシーンクラス
* @todo 現在テンプレートの為ヘッダに実装をかいている
*/
template<typename entry_type>
class StateMachine
{

public:
	/**
	* Constructor
	* @param[out] pOwner このインスタンスを所有するクラスのインスタンスへのポインタ
	* @attention 必ずSetterでStateを設定すること
	*/
	StateMachine(entry_type* pOwner)
		: m_pOwner(pOwner)
		, m_pCurrentState(nullptr)
		, m_pPreviousState(nullptr)
	{}

	/**Destructor*/
	~StateMachine() = default;

	/**更新関数*/
	void Update()const
	{
		if(m_pCurrentState != nullptr)
		{
			m_pCurrentState->Execute(m_pOwner);
		}
		else
		{
			MessageBox(0, "Stateを設定していません。", NULL, MB_OK);
		}
	}

	/**
	* Stateを変更する関数
	* @param[in] pNewState 変更したいStateクラス継承クラスのインスタンスへのポインタ
	*/
	void ChangeState(State<entry_type>* pNewState)
	{
		m_pPreviousState = m_pCurrentState;

		m_pCurrentState->Exit(m_pOwner);

		// Stateを変更する
		m_pCurrentState = pNewState;

		m_pCurrentState->Enter(m_pOwner);
	}

	/**前のStateに戻す関数*/
	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	/**現在のStateの開始処理を呼ぶ。初期化で使用*/
	void EnterCurrentState(){ m_pCurrentState->Enter(m_pOwner); }

	//---Setter---------------------------------------------------------------------------------------//
	void SetCurrntState(State<entry_type>* pState){ m_pCurrentState = pState; }		
	void SetPreviousState(State<entry_type>* pState){ m_pPreviousState = pState; }
	
	//---Getter---------------------------------------------------------------------------------------//
	State<entry_type>* GetCurrntState() const { return m_pCurrentState; }
	State<entry_type>* GetPreviousState() const { return m_pPreviousState; }

private:
	entry_type*					m_pOwner;				//!< このインスタンスを所有するクラスのインスタンスへのポインタ
	State<entry_type>*			m_pCurrentState;		//!< 現在のStateクラス継承クラスのインスタンスへのポインタ
	State<entry_type>*			m_pPreviousState;		//!< 前のState継承クラスのインスタンスへのポインタ

};

#endif	// STATE_MACHINE_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
