/**
* @file		EffectManager.h
* @brief	EffectManagerクラスヘッダ
* @author	haga
*/

#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include <d3dx9.h>
#include <map>
#include <vector>

class Effect;

/**
* Effectクラスを管理するクラス.
*/
class EffectManager
{
public:

	/**エフェクトの種類*/
	enum EFFECT_TYPE
	{
		EXPLOSION,			//!< 爆発
	};

	/**
	* Singletonパターン<br>
	* 実体をつくる関数.
	* @return EffectManagerの実体
	*/
	static EffectManager& Instance()
	{
		static EffectManager effectManager;
		return effectManager;
	}

	/**
	* リソースIDを登録する関数
	* @param type		登録するエフェクト種類
	* @param tex_ID		テクスチャーID
	* @param vtx_ID		バーテックスID
	*/
	void RegisterID(EFFECT_TYPE type, int tex_ID, int vtx_ID);

	/**
	* エフェクトを作成する関数.
	* @param pos	位置座標
	* @param type	エフェクトの種類
	*/
	void Create(D3DXVECTOR3 pos, EFFECT_TYPE type);

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

	/**
	* 解放関数.
	* 登録したIDを全て解放する関数
	*/
	void ReleaseID();

	/**デストラクタ*/
	~EffectManager();

private:

	/**リソースIDの構造体*/
	struct RESOURCE_ID
	{
		int		TEX_ID;						//!< テクスチャーID
		int		VTX_ID;						//!< バーテックスID
	};

	std::map<EFFECT_TYPE, RESOURCE_ID>		m_EffectResurce;	//!< エフェクトのリソースを格納する変数
	std::vector<Effect*>					m_Effect;			//!< エフェクトの実体を格納する変数

	/**
	* コンストラクタ<br>
	* Singletonパターンの為private
	*/
	EffectManager();
};

#endif	// EFFECT_MANAGER_H
