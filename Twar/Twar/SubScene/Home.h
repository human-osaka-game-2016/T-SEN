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
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	* @param pSaveDataManager SaveDataManagerクラスのインスタンスへのポインタ
	*/
	Home(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	virtual ~Home();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();


};

}

#endif // HOME_H
