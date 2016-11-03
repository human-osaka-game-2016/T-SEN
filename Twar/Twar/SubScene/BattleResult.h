/**
* @file BattleResult.h
* @brief BattleResultクラスヘッダ 
* @author haga
*/
#ifndef BATTLE_RESULT_H
#define BATTLE_RESULT_H

#include "SubScene.h"

namespace sub_scene
{

/**
* 戦闘結果表示シーンのクラス
*/
class BattleResult :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pSaveDataManager SaveDataManagerクラスのインスタンスへのポインタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	BattleResult(SaveDataManager* pSaveDataManager, GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~BattleResult();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

}

#endif // BATTLE_RESULT_H

