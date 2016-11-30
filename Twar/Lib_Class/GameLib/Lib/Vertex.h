/**
* @file		Vertex.h
* @brief	Vertexクラスヘッダ
* @author	haga
*/
#ifndef VERTEX_H
#define VERTEX_H

#include "GraphicsDevice.h"

/**
* バーテックス構造体.
*/
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;	//!< 座標系
	DWORD	color;			//!< 色
	FLOAT	tu, tv;			//!< tu,tv値
};

/**
* バーテックス(頂点情報)を管理するクラス
*/
class Vertex
{
private:
	IDirect3DDevice9*		m_pD3Device;			//!< Direct3Dのデバイス
	float					m_VtxWidth;		  	    //!< バーテックスの横幅
	float					m_VtxHeight;			//!< バーテックスの縦幅
	float					m_VtxDepth;				//!< バーテックスの奥行き
	float					m_TuMin;				//!< バーテックスのtu最小値
	float					m_TuMax;				//!< バーテックスのtu最大値
	float					m_TvMin;				//!< バーテックスのtv最小値
	float					m_TvMax;				//!< バーテックスのtv最大値
	DWORD                   m_Color[4];				//!< バーテックスの色の値

public:

	/**
	* コンストラクタ.
	* 数値を指定するときに使用<br>
	* 奥行も指定する場合に作成.
	* @param[in] width	幅
	* @param[in] height 高さ
	* @param[in] deoth	奥行き
	* @param[in] tuMin	tu値の最小値
	* @param[in] tuMax	tu値の最大値
	* @param[in] tvMin	tv値の最小値
	* @param[in] tvMax	tv値の最大値
	*/
	Vertex(float width = 0.0f, float height = 0.0f, float depth = 0.0f, float tuMin = 0.0f, float tuMax = 1.0f, float tvMin = 0.0f, float tvMax = 1.0f);

	/**デストラクタ*/
	~Vertex();

	/**
	* 2D通常描画関数<br>
	* バーテックスの左上の頂点に座標をセットする<br>
	* @param[in] pTexture テクスチャーへのポインタ
	* @param[in] posX     x軸の位置座標
	* @param[in] posY     y軸の位置座標
	*/
	void Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY);

	/**
	* 3D通常描画関数<br>
	* バーテックスの左上の頂点に座標をセットする<br>
	* こちらはZ座標も引数として渡す.
	* @param[in] pTexture テクスチャーへのポインタ
	* @param[in] posX     x軸の位置座標
	* @param[in] posY     y軸の位置座標
	* @param[in] posZ	  z軸の位置座標
	*/
	void Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* 2D描画関数<br>
	* バーテックスの中心に座標をセットする<br>
	* @param[in] pTexture テクスチャーへのポインタ
	* @param[in] posX     x軸の位置座標
	* @param[in] posY     y軸の位置座標
	*/
	void DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY);

	/**
	* 3D描画関数<br>
	* バーテックスの中心に座標をセットする<br>
	* Z座標も引数として渡す.
	* @param[in] pTexture テクスチャーへのポインタ
	* @param[in] posX     x軸の位置座標
	* @param[in] posY     y軸の位置座標
	* @param[in] posZ	  z軸の位置座標
	*/
	void DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* UVスクロールを行う関数
	* @param[in] scrollSpeedTu	tuのスクロールの速さ(変化量)
	* @param[in] scrollSpeedTv	tvのスクロールの速さ(変化量)
	*/
	void ScrollUV(float scrollSpeedTu, float scrollSpeedTv);

	/**
	* バーテックスサイズをセットする関数.
	* @param[in] vtxWidth  バーテックスの幅
	* @param[in] vtxHeight バーテックスの高さ
	*/
	void SetSize(float vtxWidth, float vtxHeight);

	/**
	* tu,tv値を設定する関数.
	* @param[in] tuMin tu値の最小値
	* @param[in] tuMax tu値の最大値
	* @param[in] tvMin tv値の最小値
	* @param[in] tvMax tv値の最大値
	*/
	void SetTuTvVal(float tuMin, float tuMax, float tvMin, float tvMax);

	/**
	* バーテックスの色情報を設定する関数.
	* @param[in] color  色の設定
	*/
	void SetColor(DWORD color);

	/**
	* バーテックスの横幅のサイズを取得する関数
	* @return m_VtxWidth	バーテックスの横幅
	*/
	float GetVtxWidth(){ return m_VtxWidth; }

	/**
	* バーテックスの縦幅のサイズを取得する関数
	* @return m_VtxHeight	バーテックスの縦幅
	*/
	float GetVtxHeight(){ return m_VtxHeight; }

	/**
	* バーテックスの奥行のサイズを取得する関数
	* @return m_VtxDepth	バーテックスの奥行
	*/
	float GetVtxDepth(){ return m_VtxDepth; }

};

#endif		// VERTEX_H
