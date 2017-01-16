/**
* @file SceneManager.h
* @brief SceneManagerクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../GameData/SaveDataManager.h"
#include "SceneManager.h"
#include "SceneFactory.h"

SceneManager::SceneManager()
	: m_pGameLib(&GameLib::Instance())
	, m_pSaveDataManager(new SaveDataManager())
	, m_pScene(nullptr)
	, m_CurrentSceneID(LOGO_SCENE)
	, m_NextSceneID(LOGO_SCENE)
	, m_Step(SCENE_CREATE)
	, m_IsEnd(false)
{
	SceneFactory::Instance().Init(m_pSaveDataManager);
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	delete m_pSaveDataManager;
}

// ゲーム実行関数
bool SceneManager::Run()
{
	m_pGameLib->UpdateDI();

	Control();

	m_pGameLib->StartRender();

	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	Draw();

	m_pGameLib->EndRender();

	return m_IsEnd;
}

// コントロール関数
void SceneManager::Control()
{
	switch(m_Step)
	{
	case SCENE_CREATE:

		m_CurrentSceneID = m_NextSceneID;	// シーンIDを更新

		if(m_CurrentSceneID == GAME_END)
		{	// ゲームが終了していたらフラグをたてる
			m_IsEnd = true;
			return;
		}

		m_pScene = SceneFactory::Instance().CreateScene(m_CurrentSceneID);
		m_Step = SCENE_RUN;
		break;

	case SCENE_RUN:
		if(m_pScene != nullptr)		// 念の為ここでシーンが作成されているか確認する
		{
			if(( m_NextSceneID = m_pScene->Control() ) != m_CurrentSceneID)
			{	// シーンIDが異なっていればシーンを破棄
				m_Step = SCENE_DELETE;
			}
		}
		else					// シーンができていなかったらゲームを終了する
		{
			MessageBox(0, "シーン作成に失敗しています。", NULL, MB_OK);
			m_NextSceneID = GAME_END;
			m_Step = SCENE_CREATE;
		}
		break;

	case SCENE_DELETE:
		delete m_pScene;
		m_pScene = nullptr;
		m_Step = SCENE_CREATE;
		break;
	}

}

// 描画関数
void SceneManager::Draw()
{
	if(m_pScene == nullptr)			// シーンがつくられていないなら戻る
	{
		return;
	}
	if(m_Step == SCENE_RUN)		// シーンが実行中なら描画
	{
		m_pScene->Draw();
	}
}
