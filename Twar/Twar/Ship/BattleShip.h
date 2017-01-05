/**
	@file ShipManager.h
	@brief ShipManagerクラスヘッダ
	@author kawaguchi
*/

#ifndef	BATTLESHIP_H
#define BATTLESHIP_H

#include "Ship.h"

/**
	戦艦クラス
*/
class BattleShip : public Ship
{
public:
	/**	コンストラクタ */
	BattleShip(D3DXVECTOR3* pos);

	/**	デストラクタ */
	virtual ~BattleShip();

	/**	コントロール関数 */
	virtual void Control();

	/**	描画関数 */
	virtual void Draw();

private:
	static const float		m_SpeedLimit;			//!<	限界速度

	/**	case Control of "the player" */
	virtual void ControlPlayer();

	/**	case Control of "the ally" */
	virtual void ControlAlly();

	/**	case Control of "the enemy" */
	virtual void ControlEnemy();
};

#endif	//	BATTLESHIP_H
