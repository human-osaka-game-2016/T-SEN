/**
* @file		StateFactory.h
* @brief	Statefactoryクラスヘッダ
* @author	haga
*/

#ifndef STATE_FACTORY_H
#define STATE_FACTORY_H

#include "State.h"

class StateFactory
{

public:
	static StateFactory& Instance()
	{
		static StateFactory factory;
		return factory;
	}

	~StateFactory();

	/**Stateクラスを作成する関数*/
	State* Create(State::STATE_ID stateID);

private:

	StateFactory();


};

#endif	// STATE_FACTORY_H
