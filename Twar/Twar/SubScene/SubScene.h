/**
* @file SubScene.h
* @brief  SubSceneクラスヘッダ
* @author haga
*/
#ifndef SUB_SCENE_H
#define SUB_SCENE_H

class SaveDataManager;
class GameDataManager;
class GameTimer;

namespace sub_scene
{

/**サブシーンID*/
enum SUBSCENE_ID
{
	OPENING,			//!< オープニングシーン
	HOME,				//!< 鎮守府シーン
	SHIPYARD,			//!< 造船所シーン 
	WORLD_SITUATION,	//!< 世界情勢シーン
	FORMATION,			//!< 編成シーン
	BATTLE,				//!< 戦闘シーン
	BATTLE_RESULT,		//!< 戦闘結果表示シーン
	ENDING,				//!< エンディングシーン
	GAME_CLEAR,			//!< ゲームクリア
	GAME_OVER,			//!< ゲームオーバー
};

/**
* サブシーンクラス
*/
class SubScene
{
public:
	/**コンストラクタ*/
	SubScene();

	/**デストラクタ*/
	virtual ~SubScene();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control() = 0;

	/**描画関数*/
	virtual void Draw() = 0;
protected:

	SaveDataManager* m_pSaveDataManager;		//!< SaveDataManagerクラスのインスタンスへのポインタ
	GameDataManager* m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ
	GameTimer*		 m_pGameTimer;				//!< GameTimerクラスのインスタンスへのポインタ

};

}

#endif	// SUB_SCENE_H