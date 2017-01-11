/**
* @file		Evade.h
* @brief    Evadeクラスヘッダ
* @author	haga
*/

#ifndef EVADE_H
#define EVADE_H

#include "State.h"

/**
* 逃避行動状態クラス
*/
class Evade : public State
{
public:

	Evade();
	~Evade();

	/**コントロール関数*/
	virtual State::STATE_ID Control(const Ship::STATUS& rStatus);
};

#endif	// EVADE_H
