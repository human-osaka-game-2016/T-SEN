/**
* @file		MonsterBullet.h
* @brief	MonsterBulletクラスヘッダ
* @author	haga
*/

#ifndef MONSTER_BULLET_H
#define MONSTER_BULLET_H

#include <d3dx9.h>
#include "../../Effect/EffectManager.h"

class FbxModel;
// class Collision;
class EffectManager;

/**
* モンスターが放つ弾の基底クラス
*/
class MonsterBullet
{

public:

	/**
	* コンストラクタ.
	* @param[in] pModel	モデルデータ
	* @param pos		位置座標
	* @param radian		ラジアン
	*/
	MonsterBullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float radian);

	/**デストラクタ*/
	virtual ~MonsterBullet();

	/**
	* コントロール関数.
	* @return 弾が消えたかどうか
	*/
	virtual bool Control() = 0;

	/**描画関数*/
	virtual void Draw() = 0;

	D3DXVECTOR3 GetPos(){ return m_Pos; }
	D3DXVECTOR3 GetOldPos(){ return m_OldPos; }
	float GetAngle(){ return m_Angle; }

	void SetHit(bool is){ m_IsHit = is; };

protected:
	FbxModel*			m_pModel;			//!< FbxModelクラスのインスタンスへのポインタ(モデルデータを格納)
	D3DXVECTOR3			m_Pos;				//!< 位置座標
	D3DXVECTOR3			m_OldPos;				//!< 位置座標
	D3DXMATRIX			m_MatWorld;			//!< ワールド行列
	float				m_Radian;			//!< ラジアン値
	float				m_BulletSpeedX;		//!< X軸における弾の速度
	float				m_BulletSpeedZ;		//!< Z軸における弾の速度
	bool				m_HasVanished;		//!< 弾が消えたかどうかのフラグ

	EffectManager&		m_EffectManager;
	bool				m_IsHit;
	int					m_FireCount;
	float				m_Angle;
	//Collision*			m_pCollision;	//!< 衝突判定

};

#endif // MONSTER_BULLET_H
