/**
* @file		MonsterManager.h
* @brief	MonsterManagerクラスヘッダ
* @author	haga
*/

#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include <vector>

class GameDataManager;
class FbxRelated;
class Monster;
class MonsterBulletManager;

class MonsterManager
{
public:
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

private:
	GameDataManager*		m_pGameDataManager;		//!< GameDatamanagerクラスのインスタンスへのポインタ
	FbxRelated*				m_pMonsterFbx;			//!< FbxRelatedクラスのインスタンスへのポインタ(モンスターのモデル)
	std::vector<Monster*>	m_pMonsters;			//!< Monsterクラスへのインスタンスへのポインタ
	MonsterBulletManager*	m_pBulletManager;		//!< MonsterBulletManagerクラスへのインスタンスへのポインタ

};

#endif	// MONSTER_MANAGER_H