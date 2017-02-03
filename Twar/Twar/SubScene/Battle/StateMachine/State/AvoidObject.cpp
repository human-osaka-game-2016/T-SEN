//==================================================================================================================================//
//!< @file		AvoidObject.cpp
//!< @brief		AvoidObjectクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <random>
#include "AvoidObject.h"
#include "../ShipStateManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const int		AngleCount = 7;				// 回避方向の数
const float		TurningSpeed = 0.4f;		// 旋回スピード(角度)

// 回避方向
const float		AvoidedAngles[AngleCount] = { 10.f, -30.f, 60.f, -80.f, -100.f, 180.f, -240.f, };
const int		AvoidedTime = 120 ;			// 回避を行う時間

}

//--------------------------------------------------------------------------------------------------------------//
//Static variable
//--------------------------------------------------------------------------------------------------------------//

AvoidObject*	AvoidObject::m_pAvoidObject = nullptr;

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

void AvoidObject::Enter(Ship* pShip)
{
	pShip->SetIsHit(false);
	pShip->SetOldRotate(pShip->GetRotate());
	std::random_device seed_gen;
	std::mt19937 mt(seed_gen());
	std::uniform_int_distribution<> dist(0, (AngleCount - 1));

	float rotate =  AvoidedAngles[dist(mt)];

	if(rotate < 0.f)
	{
		pShip->SetTurningSpeed(-TurningSpeed);
	}
	else
	{
		pShip->SetTurningSpeed(TurningSpeed);
	}

	pShip->SetTargetAngle(rotate);
	pShip->SetAvoidedTimeCount(0);
}

void AvoidObject::Execute(Ship* pShip)
{
	float shipAngle = pShip->GetRotate();
	float targetAngle = pShip->GetToTargetAngle();

	float turningSpeed = pShip->GetTurningSpeed();
	shipAngle += turningSpeed;
	D3DXVECTOR3 vecAxisZ = { 0.0f, 0.0f, 1.0f };

	D3DXMATRIX		matRotation;						// 回転行列
	D3DXMatrixRotationY(&matRotation, D3DXToRadian(shipAngle));
	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &matRotation);

	D3DXVECTOR3 pos = pShip->GetObjPos();
	float		speed = pShip->GetSpeedLimit();

	pos += vecAxisZ * speed;

	pShip->SetObjPos(pos);
	pShip->SetRotate(shipAngle);


	int avoidedTimeCount = pShip->GetAvoidedTimeCount();
	++avoidedTimeCount;

	if(!pShip->GetIsHit() && avoidedTimeCount >= AvoidedTime)
	{
		pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::TURNING_AROUND));
		return;
	}
	else
	{
		pShip->SetAvoidedTimeCount(avoidedTimeCount);
	}
}

void AvoidObject::Exit(Ship* pShip)
{
	pShip->SetAvoidedTimeCount(0);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
