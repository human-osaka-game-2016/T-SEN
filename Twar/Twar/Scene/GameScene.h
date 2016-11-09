/**
* @file GameScene.h
* @brief ゲームシーンのh
* @author haga
*/
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "../SubScene/SubScene.h"

class SaveDataManager;
class GameScene :public Scene
{
public:
	/**
	* コンストラクタ
	* @param[in] pSaveDataManager	セーブデータを管理するクラスのポインタ
	*/
	explicit GameScene(SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	~GameScene();

	/**コントロール関数*/
	virtual SCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	SaveDataManager*  m_pSaveDataManager;	//!< セーブデータ管理クラス
};


#endif // GAME_SCENE_H


