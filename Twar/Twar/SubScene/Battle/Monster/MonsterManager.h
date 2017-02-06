/**
* @file		MonsterManager.h
* @brief	MonsterManagerクラスヘッダ
* @author	haga
*/

#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include <vector>
#include "Monster.h"

class GameDataManager;
class FbxRelated;
class Monster;
class MonsterBulletManager;

class MonsterManager
{
public:
	typedef struct
	{
		float m_MaxX, m_MaxY, m_MaxZ;
		float m_MinX, m_MinY, m_MinZ;
		float m_MaxR;
	}MonsterSize;

	/**
	* コンストラクタ.
	* @param pGameDataManager	GameDataManagerクラスのインスタンスへのポインタ	
	*/
	explicit MonsterManager(GameDataManager* pGameDataManager);

	/**デストラクタ*/
	~MonsterManager();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

	/**ゲッター関数*/
	MonsterSize GetMonsterSize(){ return m_MonsterSize; };
	D3DXVECTOR3 GetPos(int i){ return m_pMonsters[i]->GetPos(); };

private:
	GameDataManager*		m_pGameDataManager;		//!< GameDatamanagerクラスのインスタンスへのポインタ
	FbxRelated*				m_pMonsterFbx;			//!< FbxRelatedクラスのインスタンスへのポインタ(モンスターのモデル)
	std::vector<Monster*>	m_pMonsters;			//!< Monsterクラスへのインスタンスへのポインタ
	MonsterBulletManager*	m_pBulletManager;		//!< MonsterBulletManagerクラスへのインスタンスへのポインタ
	MonsterSize				m_MonsterSize;

};

#endif	// MONSTER_MANAGER_H