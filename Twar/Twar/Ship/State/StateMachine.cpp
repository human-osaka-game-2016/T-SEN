/**
* @file		StateMachine.cpp
* @brief	StateMachineƒNƒ‰ƒXŽÀ‘•
* @author	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "StateMachine.h"
#include "StateFactory.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

StateMachine::StateMachine(const D3DXVECTOR3& rPos, float angle, float slant, float speedLimit)
	: m_pState(nullptr)
	, m_Step(ENTER)
	, m_CurrentStateID(State::PURSUIT)
	, m_NextStateID(State::PURSUIT)
	, m_Pos(rPos)
	, m_Angle(angle)
	, m_Slant(slant)
	, m_SpeedLimit(speedLimit)
{
}

StateMachine::~StateMachine()
{
	delete m_pState;
}

void StateMachine::Update()
{
	switch(m_Step)
	{
	case ENTER:
		m_CurrentStateID = m_NextStateID;
		m_pState = StateFactory::Instance().Create(m_CurrentStateID);
		m_pState->SetShipData(m_Pos,m_Angle,m_Slant,m_SpeedLimit);
		m_Step = EXECUTE;
		break;

	case EXECUTE:
		if(m_pState != nullptr)
		{
			if((m_NextStateID = m_pState->Control(m_Status)) != m_CurrentStateID)
			{
				m_Step = EXIT;
			}

			m_Pos = m_pState->GetPos();
			m_Angle = m_pState->GetAngle();
			m_Slant = m_pState->GetSlant();
			m_Status = m_pState->GetStatus();
		}
		else
		{
			m_Step = ENTER;
			m_NextStateID = State::PURSUIT;
		}
		break;

	case EXIT:
		delete m_pState;
		m_pState = nullptr;
		m_Step = ENTER;
		break;
	}
}

void StateMachine::SetStatus(const Ship::STATUS& rStatus)
{
	m_Status = rStatus;
}
