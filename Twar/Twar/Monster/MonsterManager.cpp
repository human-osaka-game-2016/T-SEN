/**
* @file		MonsterManager.cpp
* @brief	MonsterManagerクラス実装
* @author	haga
*/

#include "Fbx/FbxRelated.h"
#include "Monster.h"
#include "MonsterManager.h"


MonsterManager::MonsterManager(GameDataManager* pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_pMonsterFbx(new FbxRelated())
{
	if(!m_pMonsterFbx->LoadFbx("fbx/golem_ascii.FBX"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	// GameDataManagerから敵の数をおしえてもらう
	/**@todo	現在はまだ実装できていないで、適当に敵を作成*/
	m_pMonster.emplace_back(new Monster(m_pMonsterFbx->m_pModel));
}


MonsterManager::~MonsterManager()
{
	for(auto i : m_pMonster)
	{
		delete i;
	}
	delete m_pMonsterFbx;
}

bool MonsterManager::Control()
{
	for(auto i = m_pMonster.begin(); i != m_pMonster.end();)
	{
		if((*i)->Control())		
		{// 消滅していたら削除する
			delete ( *i );
			( *i ) = nullptr;
			i = m_pMonster.erase(i);
			continue;
		}

		i++;
	}

	if(m_pMonster.size() == 0)
	{
		return true;
	}

	return false;
}

void MonsterManager::Draw()
{
	if(m_pMonster.size() > 0)
	{
		for(auto i : m_pMonster)
		{
			if(i != nullptr)
			{
				i->Draw();
			}
			
		}
	}
}
