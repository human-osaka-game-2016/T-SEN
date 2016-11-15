/**
* @file SubSceneFactory.cpp
* @brief SubSceneFactoryクラス実装
* @author haga
*/
#include "../GameData/SaveDataManager.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "SubSceneFactory.h"
#include "Opening.h"
#include "Home.h"
#include "Shipyard.h"
#include "WorldMap.h"
#include "Formation.h"
#include "Battle.h"
#include "BattleResult.h"
#include "Ending.h"


namespace sub_scene
{

SubSceneFactory::SubSceneFactory()
	: m_pSaveDataManager(nullptr)
	, m_pGameDataManager(nullptr)
	, m_pGameTimer(nullptr)
{
}

SubSceneFactory::~SubSceneFactory()
{
}

void SubSceneFactory::Init(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
{
	m_pGameDataManager = pGameDataManager;
	m_pGameTimer = pGameTimer;
	m_pSaveDataManager = pSaveDataManager;
}

SubScene* SubSceneFactory::CreateSubScene(SUBSCENE_ID subSceneID)
{
	SubScene* pSubScene = nullptr;

	switch(subSceneID)
	{
	case OPENING:
		pSubScene = new Opening();
		break;

	case HOME:
		pSubScene = new Home(m_pGameDataManager, m_pGameTimer, m_pSaveDataManager);
		break;

	case SHIPYARD:
		pSubScene = new Shipyard(m_pGameDataManager, m_pGameTimer);
		break;

	case WORLD_MAP:
		pSubScene = new WorldMap(m_pGameDataManager, m_pGameTimer);
		break;

	case FORMATION:
		pSubScene = new Formation(m_pGameDataManager);
		break;

	case BATTLE:
		pSubScene = new Battle(m_pGameDataManager, m_pGameTimer);
		break;

	case BATTLE_RESULT:
		pSubScene = new BattleResult(m_pGameDataManager, m_pGameTimer, m_pSaveDataManager);
		break;

	case ENDING:
		pSubScene = new Ending(m_pGameDataManager);
		break;

	case GAME_CLEAR:
		break;

	case GAME_OVER:
		break;

	default:
		break;
	}

	return pSubScene;
}

}
