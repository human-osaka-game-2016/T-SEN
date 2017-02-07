//==================================================================================================================================//
//!< @file		MoveToTarget.cpp
//!< @brief		MoveToTargetクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <math.h>
#include "MoveToTarget.h"
#include "../../Radar/Radar.h"
#include "../ShipStateManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const    float    FiringRange = 550.f;				// 射程範囲
const	 float	  TargetRangeLimit = 1500.f;		// ターゲットとの距離の限界値

}

//--------------------------------------------------------------------------------------------------------------//
//Static variable
//--------------------------------------------------------------------------------------------------------------//

MoveToTarget*	MoveToTarget::m_pMoveToTarget = nullptr;

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

void MoveToTarget::Enter(Ship* pShip)
{
	const D3DXVECTOR3& targetPos = Radar::Instance().GetMonsterPos();
	//const D3DXVECTOR3& targetPos = Radar::Instance().GetAIAttackTargetPos();
	const D3DXVECTOR3& shipPos = pShip->GetObjPos();

	// ターゲットへの方向を求める
	float rotate = 0.0f;
	float targetRadian = 0.0f;
	targetRadian = atan2f((targetPos.x - shipPos.x), (targetPos.z - shipPos.z));
	rotate = D3DXToDegree(targetRadian);

	// 情報を更新
	pShip->SetTargetPos(targetPos);
	pShip->SetRotate(rotate);
}

void MoveToTarget::Execute(Ship* pShip)
{
	const D3DXVECTOR3 targetPos = pShip->GetTargetPos();
	const D3DXVECTOR3 currentTargetPos = Radar::Instance().GetMonsterPos();
	if(targetPos.x != currentTargetPos.x || targetPos.z != currentTargetPos.z)
	{
		pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::TURNING_AROUND));
		return;
	}
	else
	{
		// 下記処理を行う
	}

	D3DXVECTOR3 vecLength = (pShip->GetObjPos() - pShip->GetTargetPos());
	float length = D3DXVec3Length(&vecLength);

	if(length > TargetRangeLimit)
	{
		Enter(pShip);
	}

	if(length > FiringRange)
	{
		D3DXVECTOR3 pos = pShip->GetObjPos();
		float radian = D3DXToRadian(pShip->GetRotate());
		float speed = pShip->GetSpeedLimit();
		// 前進する
		pos.x += static_cast<float>(sin(radian) * speed);
		pos.z += static_cast<float>(cos(radian) * speed);
		pShip->SetObjPos(pos);

	}
	else
	{
		pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::ATTACK_TARGET));
		return;
	}
}

void MoveToTarget::Exit(Ship* pShip)
{
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
