/**
* @file		MonsterBulletManager.h
* @brief	MonsterBulletManagerクラスヘッダ
* @author	haga
*/

#ifndef MONSTER_BULLET_MANAGER_H
#define MONSTER_BULLET_MANAGER_H

#include <d3dx9.h>
#include <vector>

class FbxRelated;
class MonsterBullet;

/**
* MonsterBulletを管理するクラス
*/
class MonsterBulletManager
{

public:
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

private:
	FbxRelated*						m_pLongRangeBulletModel;	//!< 遠距離弾のFBXモデルデータ
	FbxRelated*						m_pShortRangeBulletModel;	//!< 近距離弾のFBXモデルデータ
	std::vector<MonsterBullet*>		m_pBullets;					//!< MonsterBulletの継承クラスのインスタンスへのポインタを格納する動的配列

};

#endif // MONSTER_BULLET_MANAGER_H
