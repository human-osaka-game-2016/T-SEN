/**
* @file Opening.h
* @brief Openingクラスヘッダ
* @author haga
*/
#ifndef OPENING_H
#define OPENING_H

#include "SubScene.h"

namespace sub_scene
{

/**
* ゲームの導入シーンのクラス
*/
class Opening :public SubScene
{
public:
	/**コンストラクタ*/
	Opening();

	/**デストラクタ*/
	virtual ~Opening();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

}

#endif	// OPENING_H
