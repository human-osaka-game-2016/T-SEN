/**
* @file Policy.h
* @brief Policyクラスヘッダ
* @author haga
*/
#ifndef Policy_H
#define Policy_H

#include "../SubScene.h"

namespace sub_scene
{

/**
* 造船所シーンのクラス
*/
class Policy :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	Policy(GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~Policy();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();


};

}

#endif // Policy_H
