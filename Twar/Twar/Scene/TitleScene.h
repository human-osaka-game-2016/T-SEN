/**
* @file TitleScene.h
* @brief TitleSceneクラスヘッダ
* @author haga
*/
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Scene.h"

/**タイトルシーンの状態*/
enum TITLE_SCENE_STATE
{
	GAME_START,				//!< ゲームを開始する
	DATA_LOAD,				//!< データをロードする
	NONE,					//!< 通常状態
};

class SaveDataManager;
class TitleBackground;
class TitleLogo;
class TitleMenu;

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
	SaveDataManager*	m_pSaveDataManager;		//!< SaveDataManagerクラスのインスタンスへのポインタ
	TitleBackground*	m_pTitleBackground;		//!< TitleBackgroundクラスのインスタンスへのポインタ	
	TitleLogo*			m_pTitleLogo;			//!< TitleLogoクラスへのインスタンスへのポインタ
	TitleMenu*			m_pTitleMenu;			//!< TitleMenuクラスへのインスタンスへのポインタ
	TITLE_SCENE_STATE	m_TitleSceneState;		//!< タイトルシーンの状態 
};

#endif // TITLE_SCENE_H
