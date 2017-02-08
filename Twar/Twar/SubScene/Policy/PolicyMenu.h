/**
* @file PolicyMenu.h
* @brief PolicyMenuクラスヘッダ
* @author matsuda
*/
#include"Policy.h"

#ifndef POLICYMENU_H
#define POLICYMENU_H

class GameDataManager;
class Button;
class NumberDrawer;

class PolicyMenu
{
public:
	enum EXCHANGE_ID
	{
		IKOKU,   //威国ID
		ROKOKU,  //炉国ID
		HAKOKU,  //芳国ID

		EXCHANGE_MAX,
	};

	enum ENHANCEMENT_ID
	{
		CREATSHIP,
		DURABILITY,
		AGGRESSIVITY,
		SPEED,

		ENHANCEMENT_MAX,
	};

	enum DIGIT_ID
	{
		ONE_DIGIT,
		TEN_DIGIT,
		HUNDRED_DIGIT,
		THOUSAND_DIGIT,

		DIGIT_MAX,
	};

	enum Level_ID
	{
		LV1,
		LV2,
		LV3,
		LV4,
		LV5,
		LV6,

		LV_MAX,
	};

	PolicyMenu(GameDataManager* GameDataManager);
	~PolicyMenu();
	sub_scene::SUBSCENE_ID Control();
	void Draw();
	void MoneyBreakdownDigit(int MyMoney, int SumMoney);
	void PolicyBreakdownDigit(int EnhancementCost, int ExchangeCost);
	void InitArray();
	void InitCost();
	void AggressivityLvUP();
	void DurabilityLvUP();
	void SpeedLvUP();
	void ExchangeLvUP();
	void CreatShip();
	void MakeAccountsSquare();   //決済処理
	void Cancel();               //取り消し処理
	int EnhancementBreakdownDigit(int EnhancementCost, int Digit);
	int ExchangeBreakdownDigit(int ExchangeCost, int Digit);
private:
	GameDataManager* m_pGameDataManager;

	int m_MyMoney;     //プレイヤーの所持金額
	int m_SumMoney;    //合計金額

	int m_MyMoneyDigit[DIGIT_MAX];
	int m_SumMoneyDigit[DIGIT_MAX];
	int m_EnhancementCostDigit[DIGIT_MAX];
	int m_ExchangeCostDigit[DIGIT_MAX];
	int m_CreatShipCost[GameDataManager::SHIP_ID_MAX];            //船を造船するのに必要な金額
	int m_EnhancementCost[GameDataManager::SHIP_ID_MAX][LV_MAX];  //強化に必要な金額
	int m_Aggressivity[GameDataManager::SHIP_ID_MAX][LV_MAX];     //攻撃力
	int m_Durability[GameDataManager::SHIP_ID_MAX][LV_MAX];       //耐久力
	int m_Speed[GameDataManager::SHIP_ID_MAX][LV_MAX];            //機動力
	int m_ExchangeCost[EXCHANGE_MAX][LV_MAX];                     //交流するために必要な金額
	int m_CurrentLevel[12];                                       //現在のレベル

	Level_ID m_AggressivityLv[GameDataManager::SHIP_ID_MAX];
	Level_ID m_DurabilityLv[GameDataManager::SHIP_ID_MAX];
	Level_ID m_SpeedLv[GameDataManager::SHIP_ID_MAX];
	Level_ID m_ExchangeLv[EXCHANGE_MAX];

	Button* m_pHomeButton;
	Button* m_pPushHomeButton;
	Button* m_pSettlementButton;
	Button* m_pPushSettlementButton;
	Button* m_pCancellationButton;
	Button* m_pPushCancellationButton;
	Button* m_pExchangeFilterButton[EXCHANGE_MAX];
	Button* m_pEnhancementFilterButton[GameDataManager::SHIP_ID_MAX][ENHANCEMENT_MAX];

	D3DXVECTOR2 m_EnhancementTexPos;
	D3DXVECTOR2 m_ExchangeTexPos;
	D3DXVECTOR2 m_MyMoneyTexPos;
	D3DXVECTOR2 m_SumMoneyTexPos;
	D3DXVECTOR2 m_PolicyTexPos;
	D3DXVECTOR2 m_CreatShipTexPos[GameDataManager::SHIP_ID_MAX];

	bool m_IsPushHomeDrawn;
	bool m_IsPushSettlementDrawn;
	bool m_IsPushCancellationDrawn;
	bool m_IsExchangeFilDrawn[EXCHANGE_MAX];
	bool m_IsEnhancementFilDrawn[GameDataManager::SHIP_ID_MAX][ENHANCEMENT_MAX];

	EXCHANGE_ID m_ExchangeID;

	NumberDrawer* m_pAggressivityCost[DIGIT_MAX];
	NumberDrawer* m_pDurabilityCost[DIGIT_MAX];
	NumberDrawer* m_pSpeedCost[DIGIT_MAX];
	NumberDrawer* m_pCreatShipCost[DIGIT_MAX];
	NumberDrawer* m_pExchangeCost[DIGIT_MAX];
	NumberDrawer* m_pMyMoney;
	NumberDrawer* m_pSumMoney;
	NumberDrawer* m_pCurrentLevel[12];
	sub_scene::SUBSCENE_ID HomeBackScene();
};

#endif
