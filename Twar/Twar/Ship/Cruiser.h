/**
	@file ShipManager.h
	@brief ShipManagerクラスヘッダ
	@author kawaguchi
*/
#ifndef	CRUISER_H
#define CRUISER_H

#include "Ship.h"

/**
	巡洋艦クラス
*/
class Cruiser : public Ship
{
private:
	/**	case Control of "the player" */
	virtual void ControlPlayer();

	/**	case Control of "the ally" */
	virtual void ControlAlly();

	/**	case Control of "the enemy" */
	virtual void ControlEnemy();

	const float m_SpeedLimit = 1.5f;		//!<	限界速度

public:
	/**	コンストラクタ */
	Cruiser(D3DXVECTOR3* pos);

	/**	デストラクタ */
	~Cruiser();

	/**	コントロール関数 */
	virtual void Control();

	/**	描画関数 */
	virtual void Draw();
};

#endif	//	CRUISER_H