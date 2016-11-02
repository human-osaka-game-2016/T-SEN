/**
* @file LogoScene.h
* @brief ロゴシーンのh
* @author haga
*/
#ifndef LOGO_SCENE_H
#define LOGO_SCENE_H

#include "Scene.h"

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