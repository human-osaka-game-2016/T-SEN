/**
* @file SceneManager.h
* @brief シーンを管理するクラスSceneManagerのcpp
* @author haga
*/
#include "GameLib/GameLib.h"
#include "SceneManager.h"

SceneManager::SceneManager():
m_pGameLib(&GameLib::GetInstance()),
m_pScene(nullptr),
m_currentSceneID(LOGO_SCENE),
m_nextSceneID(LOGO_SCENE),
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
}

// ゲーム実行関数
bool SceneManager::Run()
{
	m_pGameLib->UpDateDI();

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
		m_step = SCENE_RUN;
		break;

	case SCENE_RUN:
		if ((m_nextSceneID = m_pScene->Control()) != m_currentSceneID)
		{	// シーンIDが異なっていれば
			m_step = SCENE_DELETE;
		}
		break;

	case SCENE_DELETE:
		delete m_pScene;
		m_step = SCENE_CREATE;
		break;
	}

}

// 描画関数
void SceneManager::Draw()
{
	if (m_step == SCENE_RUN)		// シーンが実行中なら描画
	{
		m_pScene->Draw();
	}
}