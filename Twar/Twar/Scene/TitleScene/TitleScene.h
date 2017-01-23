/**
* @file TitleScene.h
* @brief TitleSceneクラスヘッダ
* @author haga
*/
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "../Scene.h"

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
	/**タイトルシーンの状態*/
	enum STATE
	{
		GAME_START,				//!< ゲームを開始する
		DATA_LOAD,				//!< データをロードする
		NONE,					//!< 通常状態
	};

	/**TextureID*/
	enum TEXTURE_ID
	{
		BACKGROUND_TEX,			//!< タイトル背景
		LOGO_TEX,				//!< タイトルロゴ
		BUTTON_TEX,				//!< タイトルで使用するボタン
		SAVE_DATA_TEX,			//!< セーブデータスロット関連
		TEX_MAX
	};

	/**VertexID*/
	enum VERTEX_ID
	{
		BACKGROUND_VTX,				//!< タイトル背景
		LOGO_VTX,					//!< タイトルロゴ
		START_BTN_VTX,				//!< スタートボタン
		CONTINUE_BTN_VTX,			//!< コンティニューボタン
		RETURN_BTN_VTX,				//!< 戻るボタン(セーブ画面で使用する)
		SAVE_SLOT_VTX,				//!< セーブスロット
		AUTO_SAVE_VTX,				//!< オートセーブスロット
		SAVE_DATA_VTX,				//!< 現在選んでいるセーブデータを表示する画面 
		VTX_MAX
	};
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
	STATE				m_TitleSceneState;		//!< タイトルシーンの状態 

	/**
	* 初期化関数<br>
	* テクスチャー読み込みなどを行う
	*/
	void Init();
};

#endif // TITLE_SCENE_H
