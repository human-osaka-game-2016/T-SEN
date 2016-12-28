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
class ShortRangeBullet : public MonsterBullet
{

public:
	/**
	* コンストラクタ.
	* @param[in] pModel	モデルデータ
	* @param pos		位置座標
	* @param radian		ラジアン値
	*/
	ShortRangeBullet(FbxModel* pModel, const D3DXVECTOR3& rPos, float radian);

	/**デストラクタ*/
	~ShortRangeBullet();

	/**
	* コントロール関数.
	* @return 弾が消えたかどうか
	*/
	virtual bool Control();

	/**描画関数*/
	virtual void Draw();

private:
	float			m_BulletSpeedY;			//!< Y軸における弾の速度 
	int				m_FlyingTimeCount;		//!< 弾が飛んでいる時間をカウントする変数
	int				m_StanbyTime;			//!< 弾の発射までの待機時間
	int				m_StanbyTimeCount;		//!< 待機時間をカウント

};

#endif	// SHORT_RANGE_BULLET_H
