/**
* @file		MonsterManager.cpp
* @brief	MonsterManagerクラス実装
* @author	haga
*/

//---------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//---------------------------------------------------------------------------------------------------------------------------------------//

#include "Fbx/FbxRelated.h"
#include "../../../GameData/GameDataManager.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "MonsterBullet/MonsterBulletManager.h"
#include "../BattleData/BattleDataManager.h"

//---------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//---------------------------------------------------------------------------------------------------------------------------------------//

MonsterManager::MonsterManager(GameDataManager* pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_pMonsterFbx(new FbxRelated())
	, m_pBulletManager(new MonsterBulletManager())
{
	if(!m_pMonsterFbx->LoadFbx("fbx/golem_ascii.FBX"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	// GameDataManagerから敵の数をおしえてもらう
	/**@todo	現在はまだ実装できていないで、適当に敵を作成*/
	m_pMonsters.emplace_back(new Monster(m_pMonsterFbx->m_pModel, m_pBulletManager));

	BattleDataManager::Instance().SetMonsterCount(sizeof(m_pMonsters));

	m_MonsterSize.m_MaxX = m_pMonsterFbx->m_pModel->maxX;
	m_MonsterSize.m_MaxY = m_pMonsterFbx->m_pModel->maxY;
	m_MonsterSize.m_MaxZ = m_pMonsterFbx->m_pModel->maxZ;
	m_MonsterSize.m_MinX = m_pMonsterFbx->m_pModel->minX;
	m_MonsterSize.m_MinY = m_pMonsterFbx->m_pModel->minY;
	m_MonsterSize.m_MinZ = m_pMonsterFbx->m_pModel->minZ;
	m_MonsterSize.m_MaxR = m_pMonsterFbx->m_pModel->maxR;

}


MonsterManager::~MonsterManager()
{
	for(auto monster : m_pMonsters)
	{
		delete monster;
	}
	m_pMonsters.clear();

	delete m_pBulletManager;

	delete m_pMonsterFbx;
}

void MonsterManager::Control()
{
	for(auto itr = m_pMonsters.begin(); itr != m_pMonsters.end();)
	{
		if((*itr)->Control())		
		{// 消滅していたら削除する
			delete (*itr);
			itr = m_pMonsters.erase(itr);
			BattleDataManager::Instance().SetMonsterCount(static_cast<int>(m_pMonsters.size()));
		}
		else
		{
			++itr;
		}
	}

	m_pBulletManager->Control();
}

void MonsterManager::Draw()
{
	for(auto itr = m_pMonsters.begin(); itr != m_pMonsters.end(); ++itr)
	{
		(*itr)->Draw();
	}

	m_pBulletManager->Draw();
}
