/**
	@file ShipManager.h
	@brief ShipManagerクラスヘッダ
	@author kawaguchi
*/

#ifndef	DESTROYER_H
#define DESTROYER_H

#include "Ship.h"

/**
	駆逐艦クラス
*/
class Destroyer : public Ship
{
public:
	/**	コンストラクタ */
	Destroyer(D3DXVECTOR3* pos, BulletManager* pBulletManager);

	/**	デストラクタ */
	~Destroyer();

	/**	コントロール関数 */
	virtual void Control();

	/**	描画関数 */
	virtual void Draw();

private:
	/**	case Control of "the player" */
	virtual void ControlPlayer();

	/**	case Control of "the ally" */
	virtual void ControlAlly();

	/**	case Control of "the enemy" */
	virtual void ControlEnemy();
};

#endif	//	DESTROYER_H
