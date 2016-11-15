/**
* @file LogoScene.h
* @brief LogoSceneクラスヘッダ
* @author haga
*/
#ifndef LOGO_SCENE_H
#define LOGO_SCENE_H

#include "Scene.h"

/**
* ロゴシーンのクラス
*/
class LogoScene :public Scene
{
public:
	/**コンストラクタ*/
	LogoScene();
	/**デストラクタ*/
	virtual~LogoScene();
	/**コントロール関数*/
	virtual SCENE_ID Control();
	/**描画関数*/
	virtual void Draw();
};

#endif	// LOGO_SCENE_H
