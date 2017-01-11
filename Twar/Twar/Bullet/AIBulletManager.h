/**
* @file		AIBulletManager.h
* @brief	AIBulletManagerクラスヘッダ
* @author	haga
*/

#ifndef AI_BULLET_MANAGER_H
#define AI_BULLET_MANAGER_H

#include <d3dx9.h>
#include <vector>

class ApBullet;
class Bullet;
class FbxRelated;

/**
* AIのBulletManagerクラス
*/
class AIBulletManager
{
public:
	static  AIBulletManager&	Instance()
	{
		static AIBulletManager bulletManager;
		return bulletManager;
	}

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

	/**弾作成関数*/
	void Create(const D3DXVECTOR3& pos);

	~AIBulletManager();

private:
	FbxRelated*					m_BulletModel;			//!< 弾のモデル
	std::vector<Bullet*>		m_pBullets;

	AIBulletManager();

};

#endif	// AI_BULLET_MANAGER_H
