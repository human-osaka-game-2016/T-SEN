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
		AGGRESSIVITY,
		DURABILITY,
		SPEED,

		ENHANCEMENT_MAX,
	};

	PolicyMenu(GameDataManager* GameDataManager);
	~PolicyMenu();
	sub_scene::SUBSCENE_ID Control();
	void Draw();

private:
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
	D3DXVECTOR2 m_EnhancementLvUpTexPos[GameDataManager::SHIP_ID_MAX][ENHANCEMENT_MAX];
	D3DXVECTOR2 m_ExchangeLvUpTexPos[EXCHANGE_MAX];
	D3DXVECTOR2 m_CreatShipTexPos[GameDataManager::SHIP_ID_MAX];

	bool m_IsPushHomeDrawn;
	bool m_IsPushSettlementDrawn;
	bool m_IsPushCancellationDrawn;
	bool m_IsExchangeFilDrawn[EXCHANGE_MAX];
	bool m_IsEnhancementFilDrawn[GameDataManager::SHIP_ID_MAX][ENHANCEMENT_MAX];

	EXCHANGE_ID m_ExchangeID;


	sub_scene::SUBSCENE_ID HomeBackScene();
};

#endif
