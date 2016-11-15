/**
* @file SubSceneFactory.h
* @brief SubSceneFactoryクラスヘッダ
* @author haga
*/
#ifndef SUB_SCENE_FACTORY_H
#define SUB_SCENE_FACTORY_H

#include "SubScene.h"

class SaveDataManager;
class GameDataManager;
class GameTimer;


namespace sub_scene
{

/**
* サブシーンを作成するファクトリークラス
*/
class SubSceneFactory
{
public:
	/**
	* 実体を取得する関数<br>
	* Singletonパターン
	* return SubSceneFactoryのインスタンス
	*/
	static SubSceneFactory& Instance()
	{
		static SubSceneFactory subSceneFactory;

		return subSceneFactory;
	}

	/**
	* 初期化関数
	* @param[in] pGameDataManager	GameDataManagerクラスのインスタンスへのポインタ
	* @param[in] pGameTimer			GameTimerクラスのインスタンスへのポインタ
	* @param[in] pSaveDataManager	SaveDataManagerクラスのインスタンスへのポインタ
	*/
	void Init(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager);

	/**
	* サブシーンを作成する関数<br>
	* @param subSceneID	サブシーンID
	* @return 作成したサブシーンのインスタンスへのポインタ
	*/
	SubScene* CreateSubScene(SUBSCENE_ID subSceneID);

	/**デストラクタ*/
	~SubSceneFactory();

private:
	/**
	* コンストラクタ<br>
	* Singletonパターンの為private
	*/
	SubSceneFactory();

	SaveDataManager* m_pSaveDataManager;		//!< SaveDataManagerクラスのインスタンスへのポインタ
	GameDataManager* m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ
	GameTimer*		 m_pGameTimer;				//!< GameTimerクラスのインスタンスへのポインタ

};

}

#endif	// SUB_SCENE_FACTORY_H
