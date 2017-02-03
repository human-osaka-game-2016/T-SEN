//==================================================================================================================================//
//!< @file		AIBullet.h
//!< @brief		AIBulletクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef AI_BULLET_H
#define AI_BULLET_H

#include <d3dx9.h>

class FbxModel;

/**
* 軍艦AIが発射する弾
*/
class AIBullet
{

public:
	/**
	* Constructor
	* @param[in] pModel	モデルデータ
	* @param pos		位置座標
	* @param radian		ラジアン
	*/
	AIBullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float radian);

	/**Desutructor*/
	~AIBullet();

	/**コントロール関数*/
	bool Control();

	/**描画関数*/
	void Draw();

private:
	FbxModel*			m_pModel;				//!< FbxModelクラスのインスタンスへのポインタ(モデルデータを格納)
	D3DXVECTOR3			m_Pos;					//!< 位置座標
	D3DXMATRIX			m_MatWorld;				//!< ワールド行列
	float				m_Radian;				//!< ラジアン値
	float				m_BulletSpeedX;			//!< X軸における弾の速度
	float				m_BulletSpeedY;			//!< Y軸における弾の速度
	float				m_BulletSpeedZ;			//!< Z軸における弾の速度
	int					m_FlyingTimeCount;		//!< 弾が飛んでいる時間をカウントする変数
	bool				m_HasVanished;			//!< 弾が消えたかどうかのフラグ
	LPD3DXMESH			m_pMesh;				//!< 仮の弾を発射するメッシュ

};

#endif	// AI_BULLET_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
