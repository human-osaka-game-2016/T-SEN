/**
* @file   Vertex.h
* @brief  バーテックスクラス
* @author haga
*/
#ifndef VERTEX_H
#define VERTEX_H

#include "GraphicsDevice.h"

/**
* カスタムバーテックス構造体.
*/
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;	//!< 座標系
	DWORD	color;			//!< 色
	FLOAT	tu, tv;			//!< テクスチャーのtu,tv値
};


/**
* バーテックスクラス
*/
class Vertex
{
private:
	IDirect3DDevice9*		m_pD3Device;			//!< デバイス
	float					m_texWidth;		  	    //!< テクスチャーの幅
	float					m_texheight;			//!< テクスチャーの高さ
	float					m_texDepth;				//!< テクスチャーの奥行き
	float					m_tuMax;				//!< テクスチャーのtu最大値
	float					m_tuMin;				//!< テクスチャーのtu最小値
	float					m_tvMax;				//!< テクスチャーのtv最大値
	float					m_tvMin;				//!< テクスチャーのtv最小値
	DWORD                   m_color[4];				//!< 色の値

public:
	
	/**
	* コンストラクタ.
	* 数値を指定するときに使用<br>
	* 奥行も指定する場合に作成.
	* @param[in] width  幅
	* @param[in] height 高さ
	* @param[in] deoth	奥行き
	* @param[in] tuMax	 tu値の最大値
	* @param[in] tvMax	 tv値の最大値
	* @param[in] tuMin	 tu値の最小値
	* @param[in] tvMin	 tv値の最小値
	*/
	Vertex(float width = 0.0f,float height = 0.0f,float depth = 0.0f,float tuMax = 1.0f,float tvMax = 1.0f,float tuMin = 0.0f,float tvMin = 0.0f);

	/**デストラクタ*/
	~Vertex();

	/**
	* 通常描画関数<br>
	* テクスチャーの左上に座標をセットする<br>
	* @param[in] texture テクスチャークラスのポインタ
	* @param[in] posX     X座標
	* @param[in] posY     Y座標
	*/
	void Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY);

	/**
	* 通常描画関数<br>
	* テクスチャーの左上に座標をセットする<br>
	* こちらはZ座標も引数として渡す.
	* @param[in] texture テクスチャークラスのポインタ
	* @param[in] posX     X座標
	* @param[in] posY     Y座標
	* @param[in] posZ	  Z座標(デフォルト引数は0.0f)
	*/
	void Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* 描画関数<br>
	* テクスチャーの中心に座標をセットする<br>
	* @param[in] texture テクスチャークラスのポインタ
	* @param[in] posX     X座標
	* @param[in] posY     Y座標
	*/
	void DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY);

	/**
	* 描画関数<br>
	* テクスチャーの中心に座標をセットする<br>
	* Z座標も引数として渡す.
	* @param[in] texture テクスチャークラスのポインタ
	* @param[in] posX     X座標
	* @param[in] posY     Y座標
	* @param[in] posZ	  Z座標(デフォルト引数は0.0f)
	*/
	void DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* テクスチャーサイズをセットする関数.
	* @param[in] texWidth  テクスチャーの幅
	* @param[in] texHeight テクスチャーの高さ
	*/
	void SetTexSize(float texWidth, float texHeight);

	/**
	* tu,tv値を設定する関数.
	* @param[in] tuMin tu値の最小値
	* @param[in] tuMax tu値の最大値
	* @param[in] tvMin tv値の最小値
	* @param[in] tvMax tv値の最大値
	*/
	void SetTuTvVal(float tuMin,float tuMax, float tvMin,float tvMax);

	/**
	* テクスチャー色をセットする関数.
	* @param[in] color  色の設定
	*/
	void SetColor(DWORD color);

};

#endif