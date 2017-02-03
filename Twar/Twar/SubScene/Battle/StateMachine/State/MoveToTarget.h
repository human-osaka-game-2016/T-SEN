#ifndef MOVE_TO_TARGET_H
#define MOVE_TO_TARGET_H

#include "State.h"
#include "../../Ship/Ship.h"

class MoveToTarget : public State<Ship>
{

public:
	/**Constrctor*/
	MoveToTarget();

	/**Destrctor*/
	~MoveToTarget();

};

#endif	// MOVE_TO_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
