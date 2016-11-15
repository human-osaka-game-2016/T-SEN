/**
* @file SceneManager.h
* @brief SceneManegerクラスヘッダ
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
	/**シーン処理ステップ*/
	enum STEP
	{
		SCENE_CREATE,		//!< シーンを生成する
		SCENE_RUN,			//!< シーンを実行する
		SCENE_DELETE		//!< シーンを削除する
	};

	GameLib*		  m_pGameLib;			//!< ライブラリ
	SaveDataManager*  m_pSaveDataManager;	//!< SaveDataManagerクラスのインスタンスへのポインタ
	Scene*			  m_pScene;				//!< Sceneの継承クラスのインスタンスへのポインタ
	SCENE_ID          m_CurrentSceneID;		//!< 現在のシーンID
	SCENE_ID		  m_NextSceneID;		//!< 次のシーンID
	STEP			  m_Step;				//!< 処理ステップ
	bool			  m_IsEnd;				//!< 終了フラグ

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

};

#endif	// SCENE_MANAGER_H
