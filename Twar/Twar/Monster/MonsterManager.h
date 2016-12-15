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

class MonsterManager
{
public:
	MonsterManager(GameDataManager* pGameDataManager);

	~MonsterManager();

	bool Control();

	void Draw();

private:
	GameDataManager*		m_pGameDataManager;		//!< GameDatamanagerクラスのインスタンスへのポインタ
	FbxRelated*				m_pMonsterFbx;			//!< FbxRelatedクラスのインスタンスへのポインタ(モンスターのモデル)
	std::vector<Monster*>	m_pMonster;				//!< Monsterクラスへのインスタンスへのポインタ

};

#endif	// MONSTER_MANAGER_H