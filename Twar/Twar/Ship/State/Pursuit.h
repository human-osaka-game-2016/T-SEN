/**
* @file		Pursuit.h
* @brief	Pursuitクラスヘッダ
* @author	haga
*/

#ifndef PURSUIT_H
#define PURSUIT_H

#include "State.h"

/**
* 追跡行動の状態クラス
*/
class Pursuit : public State
{

public:

	Pursuit();

	~Pursuit();

	/**コントロール関数*/
	virtual State::STATE_ID Control(const Ship::STATUS& rStatus);

};

#endif	// PURSUIT_H
