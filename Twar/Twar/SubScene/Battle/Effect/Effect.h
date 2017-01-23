/**
* @file		Effect.h
* @brief	Effectクラスヘッダ
* @author	haga
*/

#ifndef EFFECT_H
#define EFFECT_H

#include <d3dx9.h>

class Effect
{
public:
	/**
	* コンストラクタ.
	* @param pos	位置座標
	* @param texID	テクスチャーのID
	* @param vyxID	バーテックスのID
	*/
	Effect(D3DXVECTOR3 pos, int texID, int vtxID);

	/**dデストラクタ*/
	virtual ~Effect();

	/**
	* コントロール関数.
	* @return エフェクトが終了した場合はtrueがかえってくる 
	*/
	virtual bool Control() = 0;

	/**描画関数*/
	virtual void Draw() = 0;

protected:
	D3DXVECTOR3		m_Pos;					//!< 位置座標
	D3DXMATRIX		m_MatWorld;				//!< ワールド座標
	int				m_TexID;				//!< テクスチャーID
	int				m_VtxID;				//!< バーテックスID
	int				m_AnimeTimeCount;		//!< アニメ時間カウント変数
	int				m_AnimePatternCount;	//!< アニメパターンのカウント数
	bool			m_IsEnd;				//!< エフェクトが終わったかどうか

	/**座標を3D空間に変換する関数*/
	void Transform3D();

	/**ビルボード処理を行う関数*/
	void TransformBillboard();

};

#endif	// EFFECT_H
