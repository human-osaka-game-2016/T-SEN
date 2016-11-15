/**
* @file   TitleScene.h
* @brief  TitleSceneクラスヘッダ
* @author haga
*/
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Scene.h"

class SaveDataManager;

/**
* タイトルシーンのクラス
*/
class TitleScene :public Scene
{
public:
	/**
	* コンストラクタ
	* @param[in] pSaveDataManager SaveDataManagerクラスのインスタンスへのポインタ
	*/
	explicit TitleScene(SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	virtual~TitleScene();

	/**コントロール関数*/
	virtual SCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	SaveDataManager*  m_pSaveDataManager;	//!< SaveDataManagerクラスのインスタンスへのポインタ
};

#endif // TITLE_SCENE_H
