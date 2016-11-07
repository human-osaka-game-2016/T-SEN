/**
* @file Home.h
* @brief Homeクラスヘッダ
* @author haga
*/
#ifndef HOME_H
#define HOME_H

#include "SubScene.h"

namespace sub_scene
{

/**
* 鎮守府シーンのクラス
*/
class Home :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pSaveDataManager SaveDataManagerクラスのインスタンスへのポインタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	Home(SaveDataManager* pSaveDataManager, GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~Home();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();


};

}

#endif
