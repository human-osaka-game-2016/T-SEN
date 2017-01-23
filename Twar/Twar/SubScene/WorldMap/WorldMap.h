/**
* @file WorldMap.h
* @brief WorldMapクラスヘッダ
* @author haga
*/
#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include "../SubScene.h"

namespace sub_scene
{

/**
* 情勢(外交などを行う)シーンのクラス
*/
class WorldMap :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	WorldMap(GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~WorldMap();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

}

#endif // WORLD_MAP_H
