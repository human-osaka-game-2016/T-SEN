/**
* @file GameScene.cpp
* @brief GameSceneクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "GameScene.h"
#include "../GameData/SaveDataManager.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "../SubScene/SubSceneFactory.h"


GameScene::GameScene(SaveDataManager* pSaveDataManager)
	: m_pSaveDataManager(pSaveDataManager)
	, m_pGameDataManager(new GameDataManager())
	, m_pGameTimer(new GameTimer())
	, m_pSubScene(nullptr)
	, m_Step(CREATE_SUBSCENE)
	, m_CurrentSubSceneID(sub_scene::OPENING)
	, m_NextSubSceneID(sub_scene::OPENING)
{
}


GameScene::~GameScene()
{
	if (m_pSubScene != nullptr)
	{
		delete m_pSubScene;
		m_pSubScene = nullptr;
	}
	delete m_pGameTimer;
	delete m_pGameDataManager;
}

// コントロール関数
SCENE_ID GameScene::Control()
{
	if (m_pSubScene == nullptr)
	{
		m_CurrentSubSceneID = m_NextSubSceneID;

		if (m_CurrentSubSceneID == sub_scene::GAME_CLEAR)		// ゲームクリアならエンドロールシーンへ移行
		{
			return ENDROLL_SCENE;
		}
		else if (m_CurrentSubSceneID == sub_scene::GAME_OVER,
			m_CurrentSubSceneID == sub_scene::GAME_END)		// ゲームオーバーもしくはゲーム終了したらタイトルシーンへ移行
		{
			return TITLE_SCENE;
		}
	}

	switch (m_Step)
	{
	case CREATE_SUBSCENE:
		if (m_pSubScene == nullptr)
		{
			m_pSubScene = sub_scene::SubSceneFactory::GetInstance().CreateSubScene(m_CurrentSubSceneID);
			m_Step = RUN_SUBSCENE;
		}
		break;

	case RUN_SUBSCENE:

		if (m_pSubScene != nullptr)
		{
			if ((m_NextSubSceneID = m_pSubScene->Control()) != m_CurrentSubSceneID)
			{
				m_Step = DELETE_SUBSCENE;
			}
		}

		break;

	case DELETE_SUBSCENE:
		if (m_pSubScene != nullptr)
		{
			delete m_pSubScene;
			m_pSubScene = nullptr;
			m_Step = CREATE_SUBSCENE;
		}
		break;
	}

	return GAME_SCENE;
}

// 描画関数
void GameScene::Draw()
{
	if (m_pSubScene != nullptr && m_Step == RUN_SUBSCENE)
	{
		m_pSubScene->Draw();
	}
}