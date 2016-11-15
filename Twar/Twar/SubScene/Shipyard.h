/**
* @file Shipyard.h
* @brief Shipyardクラスヘッダ
* @author haga
*/
#ifndef SHIPYARD_H
#define SHIPYARD_H

#include "SubScene.h"

namespace sub_scene
{

/**
* 造船所シーンのクラス
*/
class Shipyard :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	Shipyard(GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~Shipyard();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();


};

}

#endif // SHIPYARD_H
