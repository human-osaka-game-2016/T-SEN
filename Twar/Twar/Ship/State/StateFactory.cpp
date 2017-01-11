/**
* @file		StateFactory.cpp
* @brief	StatefactoryƒNƒ‰ƒXŽÀ‘•
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "StateFactory.h"
#include "Pursuit.h"
#include "Attack.h"
#include "Evade.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

StateFactory::StateFactory()
{
}

StateFactory::~StateFactory()
{
}

State* StateFactory::Create(State::STATE_ID stateID)
{
	State* pState = nullptr;

	switch(stateID)
	{
	case State::PURSUIT:
		pState = new Pursuit();
		break;

	case State::EVADE:
		pState = new Evade();
		break;

	case State::ATTACK:
		pState = new Attack();
		break;

	default:
		break;
	}

	return pState;
}
