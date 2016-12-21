/**
* @file		LongRangeBullet.h
* @brief	LongRangeBulletクラスヘッダ
* @author	haga
*/

#ifndef LONG_RANGE_BULLET_H
#define LONG_RANGE_BULLET_H

#include "MonsterBullet.h"

/**
* モンスター遠距離攻撃で使用する弾<br>
*/
class LongRangeBullet : public MonsterBullet
{
public:
	LongRangeBullet();
	~LongRangeBullet();
};

#endif // LONG_RANGE_BULLET_H
