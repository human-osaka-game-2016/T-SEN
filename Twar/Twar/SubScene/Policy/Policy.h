/**
* @file Policy.h
* @brief Policyクラスヘッダ
* @author haga
*/
#ifndef Policy_H
#define Policy_H

#include "../SubScene.h"

class PolicyMenu;
class PolicyBackGround;

namespace sub_scene
{

/**
* 造船所シーンのクラス
*/
class Policy :public SubScene
{
public:
	enum TEXTUR_ID
	{
		POLICY_TEX,      //政略シーン関連のテクスチャー
		BACKGROUND_TEX,  //政略シーンのボタンのテクスチャー
		LVUP_TEX,        //LvUpボタンのテクスチャー
		CREATSHIP_TEX,   //造船ボタンのテクスチャー
	};

	enum VERTEX_ID
	{
		BACKGROUND_VTX,
		HOME_BUTTON_VTX,
		HOME_PUSH_BUTTON_VTX,
		ENHANCEMENT_VTX,
		EXCHANGE_VTX,
		SETTLEMENT_BUTTON_VTX,
		SETTLEMENT_PUSH_BUTTON_VTX,
		CANCELLATION_BUTTON_VTX,
		CANCELLATION_PUSH_BUTTON_VTX,
		MYMONEY_VTX,
		SUMMONEY_VTX,
		POLICY_VTX,
		ENHANCEMENT_FILTER_VTX,
		EXCHANGE_FILTER_VTX,
		BLACK_FILTER_VTX,
		HYPHEN_VTX,
		SMALL_NUMBER_VTX,
		MEDIUM_NUMBER_VTX,
		LARGE_NUMBER_VTX,

		VTX_MAX,
	};

	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	Policy(GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~Policy();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	PolicyMenu* m_pPolicyMenu;
	PolicyBackGround* m_pPolicyBackGround;
	float m_PolicyTextureWidth;
	float m_PolicyTextureHeight;

	void Init();


};

}

#endif // Policy_H
