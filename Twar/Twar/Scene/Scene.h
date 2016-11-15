/**
* @file Scene.h
* @brief Sceneクラスヘッダ
* @author haga
*/

#ifndef SCENE_H
#define SCENE_H

class GameLib;
/**シーンID*/
enum SCENE_ID
{
	LOGO_SCENE,			//!< ロゴシーン
	TITLE_SCENE,		//!< タイトルシーン
	GAME_SCENE,			//!< ゲームシーン
	ENDROLL_SCENE,		//!< エンドロールシーン
	GAME_END			//!< ゲーム終了
};

/**
* シーンクラス(基底クラス)
*/
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

private:
	GameLib&		  m_rGameLib;			//!< GameLibクラス
};

#endif	// SCENE_H
