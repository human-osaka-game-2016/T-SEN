/**
* @file Scene.h
* @brief シーンの基底クラス
* @author haga
*/

#ifndef SCENE_H
#define SCENE_H

/**シーンID*/
enum SCENE_ID
{
	LOGO_SCENE,			//!< ロゴシーン
	TITLE_SCENE,		//!< タイトルシーン
	GAME_SCENE,			//!< ゲームシーン
	ENDROLL_SCENE,		//!< エンドロールシーン
	GAME_END			//!< ゲーム終了
};

class Scene
{
public:
	/**コンストタクタ*/
	Scene();

	/**デストラクタ*/
	virtual~Scene();

	/**コントロール関数*/
	virtual SCENE_ID Control() = 0;

	/**描画関数*/
	virtual void Draw() = 0;
};

#endif	// SCENE_H
