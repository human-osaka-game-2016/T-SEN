/**
* @file EndRollScene.h
* @brief EndRollSceneクラスヘッダ
* @author haga
*/
#ifndef END_ROLL_SCENE_H
#define END_ROLL_SCENE_H

#include "Scene.h"
/**
* エンドロールシーンのクラス
*/
class EndRollScene :public Scene
{
public:
	/**コンストラクタ*/
	EndRollScene();

	/**デストラクタ*/
	~EndRollScene();

	/**コントロール関数*/
	virtual SCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

#endif // END_ROLL_SCENE_H
