/**
* @file Situation.h
* @brief Situationクラスヘッダ
* @author haga
*/
#ifndef SITUATION_H
#define SITUATION_H

#include "SubScene.h"

namespace sub_scene
{

/**
* 情勢(外交などを行う)シーンのクラス
*/
class WorldSituation :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	WorldSituation(GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~WorldSituation();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

}

#endif // SITUATION_H