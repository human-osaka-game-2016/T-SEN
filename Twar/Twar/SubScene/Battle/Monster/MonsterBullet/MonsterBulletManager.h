/**
* @file		MonsterBulletManager.h
* @brief	MonsterBulletManagerクラスヘッダ
* @author	haga
*/

#ifndef MONSTER_BULLET_MANAGER_H
#define MONSTER_BULLET_MANAGER_H

#include <d3dx9.h>
#include <vector>
#include "MonsterBullet.h"

class FbxRelated;
class MonsterBullet;

/**
* MonsterBulletを管理するクラス
*/
class MonsterBulletManager
{

public:
	typedef struct
	{
		float m_MaxX, m_MaxY, m_MaxZ;
		float m_MinX, m_MinY, m_MinZ;
		float m_MaxR;
	}MonsterBulletSize;

	/**コンストラクタ*/
	MonsterBulletManager();

	/**デストラクタ*/
	~MonsterBulletManager();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

	/**
	* 遠距離弾を生成する関数.
	* @param pos	弾を生成する位置座標
	* @param radian	ラジアン値(弾の進む角度)
	*/
	void CreateLongeRangeBullet(const D3DXVECTOR3& rPos, float radian);

	/**
	* 近距離弾を生成する関数.
	* @param pos	弾を生成する位置座標
	*/
	void CreateShortRangeBullet(const D3DXVECTOR3& rPos);

	MonsterBulletSize GetMonsterBulletSize(){ return m_MonsterBulletSize; }
	int GetBulletCount(){ return static_cast<int>(m_pBullets.size()); }
	D3DXVECTOR3 GetBulletPos(int i){ return m_pBullets[i]->GetPos(); }
	D3DXVECTOR3 GetBulletOldPos(int i){ return m_pBullets[i]->GetOldPos(); }
	float GetBulletAngle(int i){ return m_pBullets[i]->GetAngle(); }

	void SetHit(int i, bool is){ m_pBullets[i]->SetHit(is); }

private:
	FbxRelated*						m_pLongRangeBulletModel;	//!< 遠距離弾のFBXモデルデータ
	FbxRelated*						m_pShortRangeBulletModel;	//!< 近距離弾のFBXモデルデータ
	std::vector<MonsterBullet*>		m_pBullets;					//!< MonsterBulletの継承クラスのインスタンスへのポインタを格納する動的配列
	MonsterBulletSize				m_MonsterBulletSize;
};

#endif // MONSTER_BULLET_MANAGER_H
