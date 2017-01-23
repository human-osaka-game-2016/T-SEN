/**
* @file		Explosion.h
* @brief	Explosionクラスヘッダ	
* @author	haga
*/

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Effect.h"

/**
* エフェクトの爆発を扱うクラス
*/
class Explosion :public Effect
{
public:

	/**
	* コンストラクタ.
	* @param pos	位置座標
	* @param texID	テクスチャーのID
	* @param vyxID	バーテックスのID
	*/
	Explosion(D3DXVECTOR3 pos, int texID, int vtxID);

	/**デストラクタ*/
	 virtual ~Explosion();

	/**
	* コントロール関数.
	* @return エフェクトが終了した場合はtrueがかえってくる 
	*/
	virtual bool Control();

	/**描画関数*/
	virtual void Draw();
};

#endif	// EXPLOSION_H
