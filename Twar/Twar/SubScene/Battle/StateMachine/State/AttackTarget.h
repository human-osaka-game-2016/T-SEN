//==================================================================================================================================//
//!< @file		AttackTarget.h
//!< @brief		AttackTarget�N���X�w�b�_
//!< @author	haga
//==================================================================================================================================//

#ifndef ATTACK_TARGET_H
#define ATTACK_TARGET_H

#include "State.h"
#include "../../Ship/Ship.h"

class AttackTarget : public State<Ship>
{

public:
	/**Constructor*/
	AttackTarget();

	/**Destructor*/
	virtual ~AttackTarget();

	/***/
	virtual void Enter(Ship*);

	/**���s�֐�*/
	virtual void Excute(Ship*);

	/***/
	virtual void Exit(Ship*);

};

#endif // ATTACK_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
