/**
* @file		VertexManager.h
* @brief	VertexManagerクラスヘッダ
* @author	haga
*/
#ifndef VERTEX_MANAGER_H
#define VERTEX_MANAGER_H

#include <map>
#include "Vertex.h"

/**
* Vertexクラスを管理するクラス.
*/
class VertexManager
{
private:
	std::map<int, Vertex> m_Vertex;				//!< バーテックスクラスを格納する変数 

public:
	/**コンストラクタ*/
	VertexManager();

	/**デストラクタ*/
	~VertexManager();

	/**
	* バーテックスクラスを作成し、登録する関数.
	* @param[in] key	登録するキー
	* @param[in] width	横幅(X軸)
	* @param[in] height 高さ(Y軸)
	* @param[in] depth  奥行(Z軸)
	* @param[in] tuMin  tu値の最小値
	* @param[in] tuMax  tu値の最大値
	* @param[in] tvMin  tv値の最小値
	* @param[in] tvMax  tv値の最大値
	*/
	void CreateVertex(int key,float width, float height, float depth = 0.0f,
		float tuMin = 0.0f, float tuMax = 1.0f, float tvMin = 0.0f,float tvMax = 1.0f);

	/**
	* 2D通常描画関数
	* @param[in] key		登録したキー
	* @param[in] pTexture   テクスチャーへのポインタ
	* @param[in] posX		x軸の位置座標
	* @param[in] posY		y軸の位置座標
	*/
	void Draw2D(int key, LPDIRECT3DTEXTURE9 pTexture,float posX,float posY);
	
	/**
	* 3D空間におけるXY平面ポリゴンの通常描画関数<br>
	* @param[in] key		登録したキー
	* @param[in] pTexture	テクスチャーへのポインタ
	* @param[in] posX		x軸の位置座標
	* @param[in] posY		y軸の位置座標
	* @param[in] posZ		z軸の位置座標
	*/
	void Draw3DXY(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* 3D空間におけるXZ平面ポリゴンの通常描画関数<br>
	* @param[in] key		登録したキー
	* @param[in] pTexture   テクスチャーへのポインタ
	* @param[in] posX		x軸の位置座標
	* @param[in] posY		y軸の位置座標
	* @param[in] posZ		z軸の位置座標
	*/
	void Draw3DXZ(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* 2D描画関数<br>
	* バーテックスの中心に座標をセットする<br>
	* @param[in] key		登録したキー
	* @param[in] pTexture   テクスチャーへのポインタ
	* @param[in] posX		x軸の位置座標
	* @param[in] posY		y軸の位置座標
	*/
	void Draw2DCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture,float posX,float posY);

	/**
	* 3D空間におけるXY平面ポリゴンの描画関数<br>
	* バーテックスの中心に座標をセットする<br>
	* @param[in] key		登録したキー
	* @param[in] pTexture	テクスチャーへのポインタ
	* @param[in] posX		x軸の位置座標
	* @param[in] posY		y軸の位置座標
	* @param[in] posZ		z軸の位置座標
	*/
	void Draw3DXYCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* 3D空間におけるXZ平面ポリゴンの描画関数<br>
	* バーテックスの中心に座標をセットする<br>
	* @param[in] key		登録したキー
	* @param[in] pTexture   テクスチャーへのポインタ
	* @param[in] posX		x軸の位置座標
	* @param[in] posY		y軸の位置座標
	* @param[in] posZ		z軸の位置座標
	*/
	void Draw3DXZCenterPos(int key, LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* UVスクロールを行う関数
	* @param[in] key			登録したキー
	* @param[in] scrollSpeedTu	tuのスクロールの速さ(変化量)
	* @param[in] scrollSpeedTv	tvのスクロールの速さ(変化量)
	*/
	void ScrollUV(int key,float scrollSpeedTu, float scrollSpeedTv);

	/**
	* サイズを変更する関数
	* @param[in] key	登録したキー
	* @param[in] width	横幅(X軸)
	* @param[in] height 高さ(Y軸)
	* @param[in] depth  奥行(Z軸)
	*/
	void SetSize(int key, float width, float height, float depth = 0.0f);

	/**
	* tu値とtv値を変更する関数
	* @param[in] key	登録したキー
	* @param[in] tuMin  tu値の最小値
	* @param[in] tuMax  tu値の最大値
	* @param[in] tvMin  tv値の最小値
	* @param[in] tvax	tv値の最大値
	*/
	void SetTuTv(int key, float tuMin, float tuMax, float tvMin, float tvMax);

	/**
	* 色を変更する関数
	* @param[in] key	登録したキー
	* @param[in] color  色
	*/
	void SetColor(int key, DWORD color);

	/**
	* バーテックスの横幅のサイズを取得する関数
	* @param key	登録したキー
	* @return バーテックスの横幅
	*/
	float GetVtxWidth(int key);

	/**
	* バーテックスの縦幅のサイズを取得する関数
	* @param key	登録したキー
	* @return バーテックスの縦幅
	*/
	float GetVtxHeight(int key);

	/**
	* バーテックスの奥行のサイズを取得する関数
	* @param key	登録したキー
	* @return バーテックスの奥行
	*/
	float GetVtxDepth(int key);

	/**
	* バーテックスを解放する関数
	* @param[in] key	登録したキー
	*/
	void Release(int key);

	/**全てのバーテックスを解放する関数*/
	void ReleaseALL();

};

#endif	// VERTEX_MANAGER_H
