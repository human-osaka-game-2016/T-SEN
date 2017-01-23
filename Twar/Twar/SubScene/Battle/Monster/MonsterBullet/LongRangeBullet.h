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
	/**
	* コンストラクタ.
	* @param[in] pModel	モデルデータ
	* @param pos		位置座標
	* @param radian		ラジアン値
	*/
	LongRangeBullet(FbxModel* pModel, const D3DXVECTOR3& rPos, float radian);

	/**デストラクタ*/
	virtual ~LongRangeBullet();

	/**
	* コントロール関数.
	* @return 弾が消えたかどうか
	*/
	virtual bool Control();

	/**描画関数*/
	virtual void Draw();

private:
	D3DXVECTOR3		m_FlyingDistanceCount;			//!< バレットの飛距離をカウント
	float			m_RollingAngle;					//!< 弾の回転角度
	bool			m_IsWithinRange;				//!< バレットが範囲内にあるかどうか

};

#endif // LONG_RANGE_BULLET_H
