/**
* @file Ending.h
* @brief Endingクラスヘッダ
* @author haga
*/
#ifndef ENDING__H
#define ENDING__H

#include "../SubScene.h"

namespace sub_scene
{

/**
* ゲームのエンディングシーンのクラス
*/
class Ending :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	*/
	explicit Ending(GameDataManager* pGameDataManager);

	/**デストラクタ*/
	virtual ~Ending();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();


};

}

#endif // ENDING__H


