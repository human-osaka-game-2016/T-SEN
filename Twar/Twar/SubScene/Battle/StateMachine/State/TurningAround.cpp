//==================================================================================================================================//
//!< @file		TurningAround.h
//!< @brief		TurningAroundクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "TurningAround.h"
#include "../../Radar/Radar.h"
#include "../ShipStateManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const	 float		TurningSpeed		= 0.4f;			// 旋回スピード
const    float		FiringRange			= 550.f;		// 射程範囲
const	 int		TurningTimeLimit	= 300;			// 旋回限界時間

}

//--------------------------------------------------------------------------------------------------------------//
//Static variable
//--------------------------------------------------------------------------------------------------------------//

TurningAround*			TurningAround::m_pTurningAround = nullptr;

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

void TurningAround::Enter(Ship* pShip)
{
	const D3DXVECTOR3& targetPos = Radar::Instance().GetMonsterPos();
	//const D3DXVECTOR3& targetPos = Radar::Instance().GetAIAttackTargetPos();
	const D3DXVECTOR3& shipPos = pShip->GetObjPos();

	// ターゲットへの方向を求める
	float targetAngle = 0.0f;
	float targetRadian = 0.0f;
	targetRadian = atan2f((targetPos.x - shipPos.x), (targetPos.z - shipPos.z));
	targetAngle = D3DXToDegree(targetRadian);

	// ターゲットの情報をセットする
	pShip->SetTargetPos(targetPos);
	pShip->SetTargetAngle(targetAngle);

	if(targetAngle < 0.f)
	{
		pShip->SetTurningSpeed(-TurningSpeed);
	}
	else
	{
		pShip->SetTurningSpeed(TurningSpeed);
	}

	pShip->SetTurningTimeCount(0);
}

void TurningAround::Execute(Ship* pShip)
{
	D3DXVECTOR3 vecLength = (pShip->GetObjPos() - pShip->GetTargetPos());
	float length = D3DXVec3Length(&vecLength);

	// 射程範囲なら攻撃へ移行する
	if(length <= FiringRange)
	{
		pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::ATTACK_TARGET));
		return;
	}

	float shipAngle = pShip->GetRotate();
	float targetAngle = pShip->GetToTargetAngle();
	float turningSpeed = pShip->GetTurningSpeed();

	if(shipAngle <= (targetAngle + TurningSpeed) && shipAngle >= (targetAngle - TurningSpeed) && turningSpeed > 0.0f)
	{
		pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::MOVE_TO_TARGET));
		return;
	}
	else if(shipAngle >= (targetAngle + TurningSpeed) && shipAngle <= (targetAngle - TurningSpeed) && turningSpeed < 0.0f)
	{
		pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::MOVE_TO_TARGET));
		return;
	}
	else
	{
		int turningTimeCount = pShip->GetTurningTimeCount();
		if(turningTimeCount >= TurningTimeLimit)
		{
			//pShip->GetStateMachine()->EnterCurrentState();
			pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::MOVE_TO_TARGET));
		}

		shipAngle += turningSpeed;

		if(shipAngle > 360.f && turningSpeed > 0.0f)
		{
			shipAngle -= 360.f;
		}
		else if(shipAngle < -360.f && turningSpeed < 0.0f)
		{
			shipAngle += 360.f;
		}
		else
		{
			// テスト用処理
		}

		D3DXVECTOR3 vecAxisZ = { 0.0f, 0.0f, 1.0f };

		D3DXMATRIX		matRotation;						// 回転行列
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(shipAngle));
		D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &matRotation);

		D3DXVECTOR3 pos = pShip->GetObjPos();
		float		speed = pShip->GetSpeedLimit();

		pos += vecAxisZ * speed;

		++turningTimeCount;

		// データ更新
		pShip->SetObjPos(pos);
		pShip->SetRotate(shipAngle);
		pShip->SetTurningTimeCount(turningTimeCount);
	}
}

void TurningAround::Exit(Ship* pShip)
{
	pShip->SetTurningTimeCount(0);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
