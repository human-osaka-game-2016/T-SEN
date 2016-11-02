/**
* @file   TitleScene.h
* @brief  タイトルシーンのh
* @author haga
*/
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Scene.h"

class SaveDataManager;
class TitleScene :public Scene
{
public:
	/**
	* コンストラクタ
	* @param[in] pSaveDataManager セーブデータを管理するクラスのポインタ
	*/
	explicit TitleScene(SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	virtual~TitleScene();

	/**コントロール関数*/
	virtual SCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	SaveDataManager*  m_pSaveDataManager;	//!< セーブデータ管理クラス
};

#endif // TITLE_SCENE_H