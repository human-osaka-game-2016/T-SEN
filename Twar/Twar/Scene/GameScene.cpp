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
	, m_step(CREATE_SUBSCENE)
	, m_currentSubSceneID(sub_scene::OPENING)
	, m_nextSubSceneID(sub_scene::OPENING)
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
		m_currentSubSceneID = m_nextSubSceneID;

		if (m_currentSubSceneID == sub_scene::GAME_CLEAR)		// ゲームクリアならエンドロールシーンへ移行
		{
			return ENDROLL_SCENE;
		}
		else if (m_currentSubSceneID == sub_scene::GAME_OVER)	// ゲームオーバーならタイトルシーンへ移行
		{
			return TITLE_SCENE;
		}
	}

	switch (m_step)
	{
	case CREATE_SUBSCENE:
		if (m_pSubScene == nullptr)
		{
			m_pSubScene = sub_scene::SubSceneFactory::GetInstance().CreateSubScene(m_currentSubSceneID);
			m_step = RUN_SUBSCENE;
		}
		break;

	case RUN_SUBSCENE:

		if (m_pSubScene != nullptr)
		{
			if ((m_nextSubSceneID = m_pSubScene->Control()) != m_currentSubSceneID)
			{
				m_step = DELETE_SUBSCENE;
			}
		}

		break;

	case DELETE_SUBSCENE:
		if (m_pSubScene != nullptr)
		{
			delete m_pSubScene;
			m_pSubScene = nullptr;
			m_step = CREATE_SUBSCENE;
		}
		break;
	}

	return GAME_SCENE;
}

// 描画関数
void GameScene::Draw()
{
	if (m_pSubScene != nullptr && m_step == RUN_SUBSCENE)
	{
		m_pSubScene->Draw();
	}
}