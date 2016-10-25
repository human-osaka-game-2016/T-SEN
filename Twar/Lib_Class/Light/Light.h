/**
* @file  Light.h
* @brief ライトに関するクラス
* @author haga
*/
#ifndef LIGHT_H
#define LIGHT_H
#include <d3dx9.h>

/**
* ライトに関するクラス
*/
class Light
{
private:
	LPDIRECT3DDEVICE9		m_pD3Device;		//!< Direct3Dのデバイス
	D3DLIGHT9				m_light;			//!< ライト構造体
	D3DXVECTOR3				m_lightPos;			//!< ライトの位置
	D3DXVECTOR3             m_direction;		//!< ライトの向き
	DWORD					m_ambientColor;		//!< アンビエント色
	

public:
	/**
	* コンストラクタ
	* @param[in] direction ライトの向き
	*/
	Light(LPDIRECT3DDEVICE9 pD3Device,D3DXVECTOR3 direction);

	/**
	* コンストラクタ
	* @param[in] lightPos  ライトの位置
	* @param[in] direction ライトの向き
	*/
	Light(LPDIRECT3DDEVICE9 pD3Device,D3DXVECTOR3 lightPos, D3DXVECTOR3 direction);

	/**デストラクタ*/
	~Light();

	/**
	* ライトアップ関数
	*/
	void LightUp();

	/**
	* ライトの種類を設定する<br>
	* D3DLIGHT_POINT,D3DLIGHT_SPOT,D3DLIGHT_DIRECTIONALの種類がある
	* @param[in] type ライトの種類 
	*/
	void SetLightType(D3DLIGHTTYPE type);

	/**
	* ライトの座標と向きをセットする
	* @param[in] pos ライトの座標
	* @param[in] direction ライトの向き
	*/
	void SetLightPos(D3DXVECTOR3 pos);

	/**
	* ライトの向きをセットする
	* @param[in] direction ライトの向き
	*/
	void SetLightDirection(D3DXVECTOR3 direction);

	/**
	* ライトの距離をセットする
	* @param[in] range ライトの」届く距離
	*/
	void SetLightRange(float range);

	/**
	* ライトのディヒューズをセットする関数
	* @param[in] dR R値 
	* @param[in] dG G値
	* @param[in] dB B値
	*/
	void SetDiffuse(float dR,float dG,float dB);

	/**
	* ライトのスペキュラをセットする関数
	* @param[in] dR R値
	* @param[in] dG G値
	* @param[in] dB B値
	*/
	void SetSpecular(float dR, float dG, float dB);
};

#endif		// LIGHT_H