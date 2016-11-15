/**
* @file SceneFactory.cpp
* @brief SceneFactoryクラス実装
* @author haga
*/
#include "Scene.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndRollScene.h"
#include "../GameData/SaveDataManager.h"
#include "SceneFactory.h"


SceneFactory::SceneFactory()
	: m_pSaveDataManager(nullptr)
{
}

SceneFactory::~SceneFactory()
{
}

// 初期化関数
void SceneFactory::Init(SaveDataManager* pSaveDataManager)
{
	m_pSaveDataManager = pSaveDataManager;
}

// シーンを作成する関数
Scene* SceneFactory::CreateScene(SCENE_ID sceneID)
{
	Scene* pScene = nullptr;

	switch(sceneID)
	{
	case LOGO_SCENE:
		pScene = new LogoScene();
		break;

	case TITLE_SCENE:
		pScene = new TitleScene(m_pSaveDataManager);
		break;

	case GAME_SCENE:
		pScene = new GameScene(m_pSaveDataManager);
		break;

	case ENDROLL_SCENE:
		pScene = new EndRollScene();
		break;

	default:
		break;
	}

	return pScene;
}
