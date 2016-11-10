/**
* @file SceneManager.h
* @brief シーンを管理するクラスSceneManagerのcpp
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/SaveDataManager.h"
#include "SceneManager.h"
#include "SceneFactory.h"

SceneManager::SceneManager():
m_pGameLib(&GameLib::GetInstance()),
m_pSaveDataManager(new SaveDataManager()),
m_pScene(nullptr),
m_currentSceneID(GAME_SCENE),
m_nextSceneID(TITLE_SCENE),
m_step(SCENE_CREATE),
m_gameEnd(false)
{
}

SceneManager::~SceneManager()
{
	if (m_pScene != nullptr)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
	delete m_pSaveDataManager;
}

// ゲーム実行関数
bool SceneManager::Run()
{
	m_pGameLib->UpDateDI();

	m_pGameLib->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

	Control();

	m_pGameLib->StartRender();

	Draw();

	m_pGameLib->EndRender();

	return m_gameEnd;
}

// コントロール関数
void SceneManager::Control()
{
	if (m_pScene == nullptr)
	{
		m_currentSceneID = m_nextSceneID;	// シーンIDを更新

		if (m_currentSceneID == GAME_END)	
		{	// ゲームが終了していたらフラグをたてる
			m_gameEnd = true;
			return;
		}
	}

	switch (m_step)
	{
	case SCENE_CREATE:
		m_pScene = SceneFactory::Instance().CreateScene(m_currentSceneID);
		m_step = SCENE_RUN;
		break;

	case SCENE_RUN:
		if (m_pScene != nullptr)		// 念の為ここでシーンが作成されているか確認する
		{
			if ((m_nextSceneID = m_pScene->Control()) != m_currentSceneID)
			{	// シーンIDが異なっていればシーンを破棄
				m_step = SCENE_DELETE;
			}
		}
		break;

	case SCENE_DELETE:
		if (m_pScene != nullptr)
		{
			delete m_pScene;
			m_pScene = nullptr;
			m_step = SCENE_CREATE;
		}
		break;
	}

}

// 描画関数
void SceneManager::Draw()
{
	if (m_pScene != nullptr && m_step == SCENE_RUN)		// シーンが実行中なら描画
	{
		m_pScene->Draw();
	}
}