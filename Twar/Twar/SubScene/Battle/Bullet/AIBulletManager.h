//==================================================================================================================================//
//!< @file		AttackTarget.h
//!< @brief		AttackTargetクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef AI_BULLET_MANAGER_H
#define AI_BULLET_MANAGER_H

#include <d3dx9.h>
#include <vector>

class AIBullet;
class FbxRelated;

/**
* AIBulletを管理するクラス
* Singltonパターン
*/
class AIBulletManager
{

public:
	/**AIBulletManagerのインスタンスを作成する関数*/
	static void Create()
	{
		if(m_pBulletManager == nullptr)
		{
			m_pBulletManager = new AIBulletManager();
		}
		else
		{
			// 作成失敗
		}
	}

	/**
	* AIBulletManagerのインスタンスを取得する関数
	* @return AIBulletManagerのインスタンス
	*/
	static AIBulletManager* Instance(){ return m_pBulletManager; }

	/**AIBulletManagerのインスタンスを破棄する関数*/
	static void Delete()
	{
		delete m_pBulletManager;
		m_pBulletManager = nullptr;
	}

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

	/**
	* 弾を作成する関数
	* @param	rPos	座標
	* @param	angle	角度
	*/
	void CreateBullet(const D3DXVECTOR3& rPos, float angle);

private:
	static AIBulletManager*			m_pBulletManager;		// AIBulletManagerクラスのインスタンスへのポインタ
	FbxRelated*						m_pBulletModel;			//!< FBXモデルデータ
	std::vector<AIBullet*>			m_pBullets;				// AIBulletクラスのインスタンスへのポインタの動的配列				

	/**Constructor*/
	AIBulletManager();

	/**Destructor*/
	~AIBulletManager();

};

#endif // AI_BULLET_MANAGER_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
