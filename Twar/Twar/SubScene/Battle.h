/**
* @file Battle.h
* @brief Battleクラスヘッダ
* @author haga
*/
#ifndef BATTLE_H
#define BATTLE_H

#include "SubScene.h"

namespace sub_scene
{

/**
* 戦闘シーンのクラス
*/
class Battle :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	Battle(GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~Battle();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

}

#endif // BATTLE_H