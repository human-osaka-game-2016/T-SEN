/**
* @file GameScene.h
* @brief GameSceneクラスヘッダ
* @author haga
*/
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "../SubScene/SubScene.h"

class SaveDataManager;
class GameDataManager;
class GameTimer;

class GameScene :public Scene
{
public:
	/**
	* コンストラクタ
	* @param[in] pSaveDataManager	SaveDataManagerクラスのインスタンスへのポインタ
	*/
	explicit GameScene(SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	~GameScene();

	/**コントロール関数*/
	virtual SCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	/**SubSceneの処理ステップ*/
	enum STEP_SUBSCENE
	{
		CREATE_SUBSCENE,		//!< SubScene生成
		RUN_SUBSCENE,			//!< SubScene実行
		DELETE_SUBSCENE			//!< SubScene破棄
	};
	SaveDataManager*	    m_pSaveDataManager;		//!< SaveDataManagerクラスのインスタンスへのポインタ
	GameDataManager*        m_pGameDataManager;		//!< GameDataManagerクラスのポインタ
	GameTimer*			    m_pGameTimer;			//!< GameTimerクラスのポインタ
	sub_scene::SubScene*    m_pSubScene;			//!< SubSceneクラスのポインタ
	STEP_SUBSCENE			m_Step;					//!< SubSceneクラスの処理ステップ
	sub_scene::SUBSCENE_ID	m_CurrentSubSceneID;	//!< 現在のSubSceneのIDを格納する変数
	sub_scene::SUBSCENE_ID	m_NextSubSceneID;		//!< 次のSubSceneのIDを格納する変数
};


#endif // GAME_SCENE_H


