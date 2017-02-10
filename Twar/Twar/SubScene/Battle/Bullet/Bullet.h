/**
* @file Bullet.h
* @brief Bulletクラスヘッダ
* @author Matsuda
*/
#ifndef BULLET_H
#define BULLET_H

#include <d3dx9.h>
#include "../Effect/EffectManager.h"

class FbxModel;
class EffectManager;

/**
*Bulletクラス
*/
class Bullet
{
	friend class BulletManager;

protected:
	//struct Data
	//{
	//	D3DXVECTOR3 BulletPos;
	//	D3DXVECTOR3 BulletOldPos;
	//	float Rotate;
	//	bool hasDrawn;
	//	bool hasInited;
	//	Data* pBefore;
	//	Data* pNext;
	//	D3DXMATRIX Matrix;
	//	bool IsHit;
	//	int FireCount;
	//};
	//Data* m_pFirst;
	//Data* m_pLast;
	//Data m_Data;
	//D3DXMATRIX m_Rotation;
	LPD3DXMESH m_pMesh;


	EffectManager&		m_EffectManager;

	D3DXVECTOR3			m_Pos;					//!< 位置座標
	D3DXVECTOR3			m_OldPos;					//!< 位置座標
	float				m_Radian;				//!< ラジアン値
	float				m_Rotate;
	bool				m_IsHit;
	int					m_FireCount;
	bool				m_HasVanished;			//!< 弾が消えたかどうかのフラグ
	float				m_BulletSpeedX;			//!< X軸における弾の速度
	float				m_BulletSpeedY;			//!< Y軸における弾の速度
	float				m_BulletSpeedZ;			//!< Z軸における弾の速度
	int					m_FlyingTimeCount;		//!< 弾が飛んでいる時間をカウントする変数
	D3DXMATRIX			m_MatWorld;				//!< ワールド行列
	D3DXVECTOR3			m_Vector;

public:
	/**コンストラクタ*/
	Bullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float angle, D3DXVECTOR3* vec, float bulletSpeed);

	/**デストラクタ*/
	virtual ~Bullet();

	/**コントロール関数*/
	virtual bool Control();
	
	/**描画関数*/
	virtual void Draw();
	
	/**最後尾につける関数*/
	//virtual void PushBack(Data* pData);
	//
	///**今あるポインターを削除して次のポインターを返す*/
	//virtual Data* EraseNext(Data* pData);
	//
	///**リストを空にする関数*/
	//virtual void Clear();

	D3DXVECTOR3 GetPos(){ return m_Pos; }
	D3DXVECTOR3 GetOldPos(){ return m_OldPos; }
	float GetRotate(){ return m_Rotate; }

protected:
	FbxModel* m_pFbx; //!<  モデルデータ

};
#endif  //BULLET_H
