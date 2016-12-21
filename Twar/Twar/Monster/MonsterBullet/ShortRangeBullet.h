/**
* @file		ShortRangeBullet.h
* @brief	ShortRangeBulletクラスヘッダ
* @autnor	haga
*/

#ifndef SHORT_RANGE_BULLET_H
#define SHORT_RANGE_BULLET_H

#include "MonsterBullet.h"

/**
* モンスター近距離攻撃で使用する弾<br>
*/
class ShortRangeBullet :public MonsterBullet
{
public:
	ShortRangeBullet();
	~ShortRangeBullet();
};

#endif	// SHORT_RANGE_BULLET_H
