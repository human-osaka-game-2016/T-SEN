/**
* @file		Attack.h
* @brief	Attackクラスヘッダ
* @author	haga
*/

#ifndef ATTACK_H
#define ATTACK_H

#include "State.h"

class Attack : public State
{

public:
	Attack();
	~Attack();

	/**コントロール関数*/
	virtual STATE_ID Control(const Ship::STATUS& rStatus);

private:
	int			m_AttackInterValCount;

};

#endif	// ATTACK_H
