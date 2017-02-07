//==================================================================================================================================//
//!< @file		ShipStateManager.cpp
//!< @brief		ShipStateManagerクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "ShipStateManager.h"
#include "State/AttackTarget.h"
#include "State/MoveToTarget.h"
#include "State/AvoidObject.h"
#include "State/TurningAround.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

void  ShipStateManager::CreateStates()
{
	AttackTarget::Create();
	MoveToTarget::Create();
	AvoidObject::Create();
	TurningAround::Create();
}

void  ShipStateManager::DeleteStates()
{
	TurningAround::Delete();
	AvoidObject::Delete();
	MoveToTarget::Delete();
	AttackTarget::Delete();
}

State<Ship>* ShipStateManager::GetShipState(SHIP_STATE_ID id)
{
	State<Ship>* pState = nullptr;

	switch(id)
	{

	case ATTACK_TARGET:
		pState = AttackTarget::Instance();
		break;
	case SEARCH_TARGET:
		break;

	case AVOID_OBJECT:
		pState = AvoidObject::Instance();
		break;

	case MOVE_TO_TARGET:
		pState = MoveToTarget::Instance();
		break;

	case TURNING_AROUND:
		pState = TurningAround::Instance();
		break;

	default:
		// do nothing
		break;

	}

	return pState;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
