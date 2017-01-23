/**
* @file BattleResult.h
* @brief BattleResultクラスヘッダ
* @author haga
*/
#ifndef BATTLE_RESULT_H
#define BATTLE_RESULT_H

#include "../SubScene.h"

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
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	* @param pSaveDataManager SaveDataManagerクラスのインスタンスへのポインタ
	*/
	BattleResult(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	virtual ~BattleResult();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

}

#endif // BATTLE_RESULT_H

