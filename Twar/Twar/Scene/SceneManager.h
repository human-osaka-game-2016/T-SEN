/**
* @file SceneManager.h
* @brief シーンを管理するクラスSceneManagerのh
* @author haga
*/
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"


class GameLib;
class SaveDataManager;
/**
* シーンを管理するクラス
*/
class SceneManager
{
private:
	/**シーン処理ステップ*/
	enum STEP
	{
		SCENE_CREATE,		//!< シーンを生成する
		SCENE_RUN,			//!< シーンを実行する
		SCENE_DELETE		//!< シーンを削除する
	};

public:
	/**コンストラクタ*/
	SceneManager();
	/**デストラクタ*/
	~SceneManager();

	/**
	* ゲーム実行関数<br>
	* @return true		ゲーム終了
    * @return false     ゲーム続行
	*/
	bool Run();

private:
	GameLib*		  m_pGameLib;			//!< ライブラリ
	SaveDataManager*  m_pSaveDataManager;	//!< セーブデータ管理クラス
	Scene*			  m_pScene;				//!< シーン
	SCENE_ID          m_currentSceneID;		//!< 現在のシーンID
	SCENE_ID		  m_nextSceneID;		//!< 次のシーンID
	STEP			  m_step;				//!< 処理ステップ
	bool			  m_gameEnd;			//!< ゲーム終了フラグ

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

};

#endif	// SCENE_MANAGER_H