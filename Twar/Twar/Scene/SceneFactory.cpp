/**
* @file SceneFactory.cpp
* @brief  シーンを作成するクラスのcpp
* @author haga
*/
#include "Scene.h"
#include "../GameData/SaveDataManager.h"
#include "SceneFactory.h"

// 初期化関数
void SceneFactory::Init(SaveDataManager* saveDataManager)
{
	m_pSaveDataManager = saveDataManager;
}

// シーンを作成する関数
Scene* SceneFactory::CreateScene(SCENE_ID sceneID)
{
	Scene* pScene = nullptr;

	switch (sceneID)
	{
	case LOGO_SCENE:
		break;

	case TITLE_SCENE:
		break;

	case GAME_SCENE:
		break;

	case ENDROLL_SCENE:
		break;

	default:
		break;
	}

	return pScene;
}