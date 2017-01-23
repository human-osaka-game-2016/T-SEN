/**
* @file Formation.h
* @brief Formationクラスヘッダ
* @author haga
*/
#ifndef FORMATION_H
#define FORMATION_H

#include "../SubScene.h"


namespace sub_scene
{

/***
* 編成シーンのクラス
*/
class Formation :public SubScene
{
public:
	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	*/
	explicit Formation(GameDataManager* pGameDataManager);

	/**デストラクタ*/
	virtual ~Formation();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

};

}
#endif // FORMATION_H
