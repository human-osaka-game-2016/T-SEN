//==================================================================================================================================//
//!< @file		SearchTarget.h
//!< @brief		SearchTargetクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef SEARCH_TARGET_H
#define SEARCH_TARGET_H

#include "State.h"
#include "../../Ship/Ship.h"

class SearchTarget : public State<Ship>
{

public:
	/**Constructor*/
	SearchTarget();

	/**Destructor*/
	~SearchTarget();

	/***/
	virtual void Enter(Ship*);

	/**実行関数*/
	virtual void Excute(Ship*);

	/***/
	virtual void Exit(Ship*);

};

#endif	// SEARCH_TARGET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
