/**
* @file PolicyMenu.h
* @brief PolicyMenuクラスヘッダ
* @author matsuda
*/
#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include "PolicyMenu.h"
#include "../../Button/BasicButton.h"
#include "../../Button/ButtonFunction/ButtonFunctionList.h"
#include "../../NumberDrawer/NumberDrawer.h"


namespace
{

	const     DWORD   BrightnessVal = 0x99999999;		    // 明度基本値
	const	  DWORD   BrightnessValMax = 0xffffffff;		// 明度最大値
	D3DXVECTOR2 ExchangeCostPos[PolicyMenu::EXCHANGE_MAX][PolicyMenu::DIGIT_MAX]
	{
		{{ 240.f, 445.f }, { 215.f, 445.f }, { 190.f, 445.f }, { 165.f, 445.f }, },
		{ { 240.f, 630.f }, { 215.f, 630.f }, { 190.f, 630.f }, { 165.f, 630.f }, },
		{ { 240.f, 815.f }, { 215.f, 815.f }, { 190.f, 815.f }, { 165.f, 815.f }, },
	};

	D3DXVECTOR2 DurabilityCostPos[GameDataManager::SHIP_ID_MAX][PolicyMenu::DIGIT_MAX]
	{
		{{ 550.f, 455.f }, { 525.f, 455.f }, { 500.f, 455.f }, { 475.f, 455.f }, },
		{ { 820.f, 455.f }, { 795.f, 455.f }, { 770.f, 455.f }, { 745.f, 455.f }, },
		{ { 1090.f, 455.f }, { 1065.f, 455.f }, { 1040.f, 455.f }, { 1015.f, 455.f }, },
	};

	D3DXVECTOR2 AggressivityCostPos[GameDataManager::SHIP_ID_MAX][PolicyMenu::DIGIT_MAX]
	{
		{{ 550.f, 635.f }, { 525.f, 635.f }, { 500.f, 635.f }, { 475.f, 635.f }, },
		{ { 820.f, 635.f }, { 795.f, 635.f }, { 770.f, 635.f }, { 745.f, 635.f }, },
		{ { 1090.f, 635.f }, { 1065.f, 635.f }, { 1040.f, 635.f }, { 1015.f, 635.f }, },
	};

	D3DXVECTOR2 SpeedCostPos[GameDataManager::SHIP_ID_MAX][PolicyMenu::DIGIT_MAX]
	{
		{{ 550.f, 815.f }, { 525.f, 815.f }, { 500.f, 815.f }, { 475.f, 815.f }, },
		{ { 820.f, 815.f }, { 795.f, 815.f }, { 770.f, 815.f }, { 745.f, 815.f }, },
		{ { 1090.f, 815.f }, { 1065.f, 815.f }, { 1040.f, 815.f }, { 1015.f, 815.f }, },
	};

	D3DXVECTOR2 CreatShipCostPos[GameDataManager::SHIP_ID_MAX][PolicyMenu::DIGIT_MAX]
	{
		{ { 550.f, 270.f }, { 525.f, 270.f }, { 500.f, 270.f }, { 475.f, 270.f }, },
		{ { 820.f, 270.f }, { 795.f, 270.f }, { 770.f, 270.f }, { 745.f, 270.f }, },
		{ { 1090.f, 270.f }, { 1065.f, 270.f }, { 1040.f, 270.f }, { 1015.f, 270.f }, },
	};

	D3DXVECTOR2 SumMoneyPos[PolicyMenu::DIGIT_MAX]
	{
		{ 1445.f, 300.f }, { 1390.f, 300.f }, { 1335.f, 300.f }, { 1280.f, 300.f },
	};

	D3DXVECTOR2 MyMoneyPos[PolicyMenu::DIGIT_MAX]
	{
		{ 1445.f, 555.f }, { 1390.f, 555.f }, { 1335.f, 555.f }, { 1280.f, 555.f },
	};

	D3DXVECTOR2 CurrentLevelPos[12]
	{
		{173.f, 355.f}, { 173.f, 540.f }, { 173.f, 725.f }, { 489.f, 360.f }, { 489.f, 540.f }, { 489.f, 725.f },
		{ 759.f, 360.f }, { 759.f, 540.f }, { 759.f, 725.f }, { 1029.f, 360.f }, { 1029.f, 540.f }, { 1029.f, 725.f }
	};
}

PolicyMenu::PolicyMenu(GameDataManager* GameDataManager)
	: m_pGameDataManager(GameDataManager)
	, m_MyMoney(m_pGameDataManager->GetMoney())
	, m_SumMoney(0)
	, m_IsPushHomeDrawn(false)
	, m_IsPushSettlementDrawn(false)
	, m_IsPushCancellationDrawn(false)
	, m_IsBattleShipSelected(false)
	, m_IsCruiserSelected(false)
{

	D3DXVECTOR2 HomeBtnPos{ 160.f, 100.f };
	m_pHomeButton = new ScaleFunction(new BasicButton(HomeBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::HOME_BUTTON_VTX));
	m_pPushHomeButton = new ScaleFunction(new BasicButton(HomeBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::HOME_PUSH_BUTTON_VTX));

	D3DXVECTOR2 SettlementBtnPos{ 1270.f, 770.f };
	m_pSettlementButton = new ScaleFunction(new BasicButton(SettlementBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SETTLEMENT_BUTTON_VTX));
	m_pPushSettlementButton = new ScaleFunction(new BasicButton(SettlementBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SETTLEMENT_PUSH_BUTTON_VTX));

	D3DXVECTOR2 CancellationBtnPos{ 1490.f, 765.f };
	m_pCancellationButton = new ScaleFunction(new BasicButton(CancellationBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::CANCELLATION_BUTTON_VTX));
	m_pPushCancellationButton = new ScaleFunction(new BasicButton(CancellationBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::CANCELLATION_PUSH_BUTTON_VTX));

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		m_pAggressivityCost[i] = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SMALL_NUMBER_VTX);
		m_pDurabilityCost[i] = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SMALL_NUMBER_VTX);
		m_pSpeedCost[i] = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SMALL_NUMBER_VTX);
		m_pCreatShipCost[i] = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SMALL_NUMBER_VTX);
		m_pExchangeCost[i] = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SMALL_NUMBER_VTX);
	}

	for (int i = 0; i < 12; i++)
	{
		m_pCurrentLevel[i] = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::MEDIUM_NUMBER_VTX);
	}
	m_pMyMoney = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::LARGE_NUMBER_VTX);
	m_pSumMoney = new NumberDrawer(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::LARGE_NUMBER_VTX);


	D3DXVECTOR2 EnhancementFilterBtnPos[GameDataManager::SHIP_ID_MAX][ENHANCEMENT_MAX]
	{
		{ { 1.0f, 1.0f }, { 470.f, 412.f }, { 470.f, 592.f }, { 470.f, 772.f }, },
		{ { 740.f, 227.f }, { 740.f, 412.f }, { 740.f, 592.f }, { 740.f, 772.f }, },
		{ { 1010.f, 227.f }, { 1010.f, 412.f }, { 1010.f, 592.f }, { 1010.f, 772.f }, },
	};

	D3DXVECTOR2 ExchangeFilterBtnPos[EXCHANGE_MAX]
	{
		{160.f, 405.f},
		{ 160.f, 590.f },
		{ 160.f, 775.f },
	};

	for (int i = 0; i < GameDataManager::SHIP_ID_MAX; i++)
	{
		m_AggressivityLv[i] = GameDataManager::LV2;
		m_DurabilityLv[i] = GameDataManager::LV2;
		m_SpeedLv[i] = GameDataManager::LV2;
		m_CreatShipCost[i] = GameDataManager::LV2;
		for (int j = 0; j < ENHANCEMENT_MAX; j++)
		{
			m_pEnhancementFilterButton[i][j] = new ScaleFunction(new BasicButton(EnhancementFilterBtnPos[i][j], sub_scene::Policy::POLICY_TEX, sub_scene::Policy::ENHANCEMENT_FILTER_VTX));
		}
	}

	for (int i = 0; i < EXCHANGE_MAX; i++)
	{
		m_ExchangeLv[i] = GameDataManager::LV2;
		m_pExchangeFilterButton[i] = new ScaleFunction(new BasicButton(ExchangeFilterBtnPos[i], sub_scene::Policy::POLICY_TEX, sub_scene::Policy::EXCHANGE_FILTER_VTX));
	}

	m_EnhancementTexPos = { 740.f, 450.f };
	m_ExchangeTexPos = { 160.f, 537.f };
	m_MyMoneyTexPos = { 1355.f, 555.f };
	m_SumMoneyTexPos = { 1355.f, 300.f };
	m_PolicyTexPos = { 1440.f, 60.0f };

	for (int i = 0; i < GameDataManager::SHIP_ID_MAX; i++)
	{
		for (int j = 0; j < ENHANCEMENT_MAX; j++)
		{
			m_IsEnhancementFilDrawn[i][j] = false;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (i <= 2)
		{
			m_CurrentLevel[i] = 0;
		}
		if (i >= 3)
		{
			m_CurrentLevel[i] = 1;
		}
	}
	InitStatus();
	InitCost();

}

PolicyMenu::~PolicyMenu()
{
	delete m_pHomeButton;
	delete m_pPushHomeButton;
	delete m_pSettlementButton;
	delete m_pPushSettlementButton;
	delete m_pCancellationButton;
	delete m_pPushCancellationButton;
	delete m_pMyMoney;
	delete m_pSumMoney;

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		delete m_pAggressivityCost[i];
		delete m_pDurabilityCost[i];
		delete m_pSpeedCost[i];
		delete m_pCreatShipCost[i];
		delete m_pExchangeCost[i];
	}

	for (int i = 0; i < GameDataManager::SHIP_ID_MAX; i++)
	{
		for (int j = 0; j < ENHANCEMENT_MAX; j++)
		{
			delete m_pEnhancementFilterButton[i][j];
		}
	}

	for (int i = 0; i < EXCHANGE_MAX; i++)
	{
		delete m_pExchangeFilterButton[i];
	}

	for (int i = 0; i < 12; i++)
	{
		delete m_pCurrentLevel[i];
	}
}

sub_scene::SUBSCENE_ID PolicyMenu::Control()
{
	MoneyBreakdownDigit(m_MyMoney, m_SumMoney);
	CreatShip();
	for (int i = 0; i < GameDataManager::SHIP_ID_MAX; i++)
	{
		for (int j = 0; j < ENHANCEMENT_MAX; j++)
		{
			if (m_pEnhancementFilterButton[i][j]->Control())
			{
				if (GameLib::Instance().ChecKMouseL() == PUSH)
				{
					m_IsEnhancementFilDrawn[i][j] = true;
				}
				else if (GameLib::Instance().ChecKMouseL() == OFF && m_IsEnhancementFilDrawn)
				{
					AggressivityLvUP();
					DurabilityLvUP();
					SpeedLvUP();
					m_IsEnhancementFilDrawn[i][j] = false;
				}
			}
			else if (!m_pEnhancementFilterButton[i][j]->Control())
			{
				m_IsEnhancementFilDrawn[i][j] = false;
			}
		}
	}

	for (int i = 0; i < EXCHANGE_MAX; i++)
	{
		if (m_pExchangeFilterButton[i]->Control())
		{
			if (GameLib::Instance().ChecKMouseL() == PUSH)
			{
				m_IsExchangeFilDrawn[i] = true;
			}
			else if (GameLib::Instance().ChecKMouseL() == OFF && m_IsExchangeFilDrawn)
			{
				ExchangeLvUP();
				m_IsExchangeFilDrawn[i] = false;
			}
		}
		else if (!m_pExchangeFilterButton[i]->Control())
		{
			m_IsExchangeFilDrawn[i] = false;
		}
	}

	if (m_pPushSettlementButton->Control())
	{
		if (GameLib::Instance().ChecKMouseL() == PUSH)
		{
			m_IsPushSettlementDrawn = true;
		}
		else if (GameLib::Instance().ChecKMouseL() == OFF && m_IsPushSettlementDrawn)
		{
			MakeAccountsSquare();
			m_IsPushSettlementDrawn = false;
		}
	}

	if (m_pPushCancellationButton->Control())
	{
		if (GameLib::Instance().ChecKMouseL() == PUSH)
		{
			m_IsPushCancellationDrawn = true;
		}
		else if (GameLib::Instance().ChecKMouseL() == OFF && m_IsPushCancellationDrawn)
		{
			Cancel();
			m_IsPushCancellationDrawn = false;
		}
	}

	// 次のシーンの選択
	sub_scene::SUBSCENE_ID	nextSubSceneID = sub_scene::SUBSCENE_ID::POLICY;
	if (m_pHomeButton->Control())
	{
		if (GameLib::Instance().ChecKMouseL() == ON)
		{
			m_IsPushHomeDrawn = true;
		}
		else if (GameLib::Instance().ChecKMouseL() == OFF && m_IsPushHomeDrawn)
		{
			m_IsPushHomeDrawn = true;
			nextSubSceneID = HomeBackScene();
			return nextSubSceneID;
		}
	}

	return nextSubSceneID;
}

void PolicyMenu::Draw()
{
	GameLib::Instance().SetVtxColor(sub_scene::Policy::ENHANCEMENT_FILTER_VTX, BrightnessVal);

	GameLib::Instance().SetVtxColor(sub_scene::Policy::EXCHANGE_FILTER_VTX, BrightnessVal);

	GameLib::Instance().DrawXYCenterPos(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::ENHANCEMENT_VTX, m_EnhancementTexPos.x, m_EnhancementTexPos.y);
	GameLib::Instance().DrawXYCenterPos(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::EXCHANGE_VTX, m_ExchangeTexPos.x, m_ExchangeTexPos.y);
	GameLib::Instance().DrawXYCenterPos(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::MYMONEY_VTX, m_MyMoneyTexPos.x, m_MyMoneyTexPos.y);
	GameLib::Instance().DrawXYCenterPos(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SUMMONEY_VTX, m_SumMoneyTexPos.x, m_SumMoneyTexPos.y);
	GameLib::Instance().DrawXYCenterPos(sub_scene::Policy::POLICY_TEX, sub_scene::Policy::POLICY_VTX, m_PolicyTexPos.x, m_PolicyTexPos.y);
	m_pHomeButton->Draw();
	m_pSettlementButton->Draw();
	m_pCancellationButton->Draw();

	bool IsDigitDrawn[GameDataManager::SHIP_ID_MAX][DIGIT_MAX];

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		m_pMyMoney->Draw(MyMoneyPos[i], m_MyMoneyDigit[i]);
		m_pSumMoney->Draw(SumMoneyPos[i], m_SumMoneyDigit[i]);
		for (int j = 0; j < GameDataManager::SHIP_ID_MAX; j++)
		{
			IsDigitDrawn[j][i] = true;
			IsDigitDrawn[0][i] = false;
			if (IsDigitDrawn[j][i])
			{
				m_pCreatShipCost[i]->Draw(CreatShipCostPos[j][i], EnhancementBreakdownDigit(m_CreatShipCost[j], i));
			}
			m_pAggressivityCost[i]->Draw(AggressivityCostPos[j][i], EnhancementBreakdownDigit(m_EnhancementCost[j][m_AggressivityLv[j]], i));
			m_pDurabilityCost[i]->Draw(DurabilityCostPos[j][i], EnhancementBreakdownDigit(m_EnhancementCost[j][m_DurabilityLv[j]], i));
			m_pSpeedCost[i]->Draw(SpeedCostPos[j][i], EnhancementBreakdownDigit(m_EnhancementCost[j][m_SpeedLv[j]], i));
		}
	}
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		for (int j = 0; j < EXCHANGE_MAX; j++)
		{
			m_pExchangeCost[i]->Draw(ExchangeCostPos[j][i], ExchangeBreakdownDigit(m_ExchangeCost[j][m_ExchangeLv[j]], i));
		}
	}

	//強化でのPush時のフィルター描画
	for (int i = 0; i < GameDataManager::SHIP_ID_MAX; i++)
	{
		for (int j = 0; j < ENHANCEMENT_MAX; j++)
		{
			m_IsEnhancementFilDrawn[GameDataManager::DESTROYER][CREATSHIP] = false;
			if (m_IsEnhancementFilDrawn[i][j])
			{
				m_pEnhancementFilterButton[i][j]->Draw();
			}
		}
	}
	//交流でのPush時のフィルター描画
	for (int i = 0; i < EXCHANGE_MAX; i++)
	{
		if (m_IsExchangeFilDrawn[i])
		{
			m_pExchangeFilterButton[i]->Draw();
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (i <= 2)
		{
			m_pCurrentLevel[i]->Draw(CurrentLevelPos[i], m_CurrentLevel[i]);
		}
		if (i >= 3)
		{
			m_pCurrentLevel[i]->Draw(CurrentLevelPos[i], m_CurrentLevel[i]);
		}
	}

	if (m_IsPushHomeDrawn)
	{
		m_pPushHomeButton->Draw();
	}
	if (m_IsPushSettlementDrawn)
	{
		m_pPushSettlementButton->Draw();
	}
	if (m_IsPushCancellationDrawn)
	{
		m_pPushCancellationButton->Draw();
	}
}

sub_scene::SUBSCENE_ID PolicyMenu::HomeBackScene()
{
	if (m_pHomeButton->Control())
	{
		return sub_scene::SUBSCENE_ID::HOME;
	}

	return sub_scene::SUBSCENE_ID::POLICY;
}

void PolicyMenu::MakeAccountsSquare()
{
	if (m_MyMoney >= m_SumMoney)
	{
		m_MyMoney -= m_SumMoney;
		m_pGameDataManager->SetMoney(m_MyMoney);
		m_pGameDataManager->SetBattleShipSelect(m_IsBattleShipSelected);
		m_pGameDataManager->SetCruiserSelect(m_IsCruiserSelected);
	}
}
void PolicyMenu::Cancel()
{
	m_SumMoney = 0;
}
void PolicyMenu::MoneyBreakdownDigit(int MyMoney, int SumMoney)
{
	int DigitCount = 1;   //求めたい桁に調整する変数
	int MyMoneyDigit[DIGIT_MAX]; //桁の値を保持する変数
	int SumMoneyDigit[DIGIT_MAX];

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		MyMoneyDigit[i] = MyMoney / DigitCount;
		m_MyMoneyDigit[i] = MyMoneyDigit[i] % 10;
		SumMoneyDigit[i] = SumMoney / DigitCount;
		m_SumMoneyDigit[i] = SumMoneyDigit[i] % 10;
		DigitCount *= 10;
	}
}

int PolicyMenu::EnhancementBreakdownDigit(int EnhancementCost, int Digit)
{
	int DigitCount = 1;   //求めたい桁に調整する変数
	int EnhancementCostDigit[DIGIT_MAX];

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		EnhancementCostDigit[i] = EnhancementCost / DigitCount;
		m_EnhancementCostDigit[i] = EnhancementCostDigit[i] % 10;
		DigitCount *= 10;
	}
	return m_EnhancementCostDigit[Digit];
}

int PolicyMenu::ExchangeBreakdownDigit(int ExchangeCost, int Digit)
{
	int DigitCount = 1;   //求めたい桁に調整する変数
	int ExchangeCostDigit[DIGIT_MAX];

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		ExchangeCostDigit[i] = ExchangeCost / DigitCount;
		m_ExchangeCostDigit[i] = ExchangeCostDigit[i] % 10;
		DigitCount *= 10;
	}
	return m_ExchangeCostDigit[Digit];
}
void PolicyMenu::InitStatus()
{
	static const int aggressivity[GameDataManager::SHIP_ID_MAX][GameDataManager::LV_MAX]
	{
		{800, 1200, 1800, 2700, 4050},
		{ 1500, 2250, 3500, 5000, 7000 },
		{ 3500, 5250, 7800, 12000, 1800 },
	};

	static const int durability[GameDataManager::SHIP_ID_MAX][GameDataManager::LV_MAX]
	{
		{2200,3300,5000,7500,12000},
		{4000,6000,9000,13500,20000},
		{10000,15000,22000,33000,50000},
	};

	static const int speed[GameDataManager::SHIP_ID_MAX][GameDataManager::LV_MAX]
	{
		{20, 22, 24},
		{ 15, 17, 19 },
		{ 10, 12, 14 },
	};

	memcpy(m_Aggressivity, aggressivity, sizeof aggressivity);
	memcpy(m_Durability, durability, sizeof durability);
	memcpy(m_Speed, speed, sizeof speed);
}
void PolicyMenu::InitCost()
{
	static const int enhancement_cost[GameDataManager::SHIP_ID_MAX][GameDataManager::LV_MAX]
	{
		{ 0, 30, 70, 100, 150 },
		{ 0, 50, 70, 100, 150 },
		{ 0, 100, 150, 200, 300 },
	};

	static const int exchange_cost[EXCHANGE_MAX][GameDataManager::LV_MAX]
	{
		{ 0, 150, 70, 150, 200},
		{ 0, 100, 30, 70, 100 },
		{ 0, 100, 30, 70, 100 },
	};

	static const int creat_ship_cost[GameDataManager::SHIP_ID_MAX]{0, 70, 200};

	memcpy(m_EnhancementCost, enhancement_cost, sizeof enhancement_cost);
	memcpy(m_ExchangeCost, exchange_cost, sizeof exchange_cost);
	memcpy(m_CreatShipCost, creat_ship_cost, sizeof creat_ship_cost);
}

void PolicyMenu::AggressivityLvUP()
{
	/*static int DestroyerShipPushCount = 0;
	static int CruiserShipPushCount = 0;
	static int BattleShipPushCount = 0;*/ //後で実装
	/*
	for (int i = 0; GameDataManager::SHIP_ID_MAX; i++)
	{
	if (m_IsEnhancementFilDrawn[i][AGGRESSIVITY])
	{
	switch (m_AggressivityLv[i])
	{
	case LV1:
	if (m_MyMoney >= m_EnhancementCost[i][LV1])
	{
	m_AggressivityLv[i] = LV2;
	m_SumMoney += m_EnhancementCost[i][LV1];
	}
	break;
	case LV2:
	if (m_MyMoney >= m_EnhancementCost[i][LV2])
	{
	m_AggressivityLv[i] = LV3;
	m_SumMoney += m_EnhancementCost[i][LV2];
	}
	break;
	case LV3:
	if (m_MyMoney >= m_EnhancementCost[i][LV3])
	{
	m_AggressivityLv[i] = LV4;
	m_SumMoney += m_EnhancementCost[i][LV3];
	}
	break;
	case LV4:
	if (m_MyMoney >= m_EnhancementCost[i][LV4])
	{
	m_AggressivityLv[i] = LV5;
	m_SumMoney += m_EnhancementCost[i][LV4];
	}
	break;
	case LV5:

	break;
	default:
	break;
	}
	}
	}*/
	if (m_IsEnhancementFilDrawn[GameDataManager::DESTROYER][AGGRESSIVITY])
	{
		switch (m_AggressivityLv[GameDataManager::DESTROYER])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV1])
			{
				m_AggressivityLv[GameDataManager::DESTROYER] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV1];
				m_CurrentLevel[4]++;
				m_pGameDataManager->SetDestroyerAggressivity(m_Aggressivity[GameDataManager::DESTROYER][m_CurrentLevel[4]], m_CurrentLevel[4]);
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV2])
			{
				m_AggressivityLv[GameDataManager::DESTROYER] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV2];
				m_CurrentLevel[4]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV3])
			{
				m_AggressivityLv[GameDataManager::DESTROYER] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV3];
				m_CurrentLevel[4]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV4])
			{
				m_AggressivityLv[GameDataManager::DESTROYER] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV4];
				m_CurrentLevel[4]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV5])
			{
				m_AggressivityLv[GameDataManager::DESTROYER] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV5];
				m_CurrentLevel[4]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
	if (m_IsEnhancementFilDrawn[GameDataManager::CRUISER][AGGRESSIVITY])
	{
		switch (m_AggressivityLv[GameDataManager::CRUISER])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV1])
			{
				m_AggressivityLv[GameDataManager::CRUISER] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV1];
				m_CurrentLevel[7]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV2])
			{
				m_AggressivityLv[GameDataManager::CRUISER] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV2];
				m_CurrentLevel[7]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV3])
			{
				m_AggressivityLv[GameDataManager::CRUISER] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV3];
				m_CurrentLevel[7]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV4])
			{
				m_AggressivityLv[GameDataManager::CRUISER] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV4];
				m_CurrentLevel[7]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV5])
			{
				m_AggressivityLv[GameDataManager::CRUISER] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV5];
				m_CurrentLevel[7]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}

	if (m_IsEnhancementFilDrawn[GameDataManager::BATTLESHIP][AGGRESSIVITY])
	{
		switch (m_AggressivityLv[GameDataManager::BATTLESHIP])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV1])
			{
				m_AggressivityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV1];
				m_CurrentLevel[10]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV2])
			{
				m_AggressivityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV2];
				m_CurrentLevel[10]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV3])
			{
				m_AggressivityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV3];
				m_CurrentLevel[10]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV4])
			{
				m_AggressivityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV4];
				m_CurrentLevel[10]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV5])
			{
				m_AggressivityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV5];
				m_CurrentLevel[10]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
}
void PolicyMenu::DurabilityLvUP()
{
	if (m_IsEnhancementFilDrawn[GameDataManager::DESTROYER][DURABILITY])
	{
		switch (m_DurabilityLv[GameDataManager::DESTROYER])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV1])
			{
				m_DurabilityLv[GameDataManager::DESTROYER] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV1];
				m_CurrentLevel[3]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV2])
			{
				m_DurabilityLv[GameDataManager::DESTROYER] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV2];
				m_CurrentLevel[3]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV3])
			{
				m_DurabilityLv[GameDataManager::DESTROYER] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV3];
				m_CurrentLevel[3]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV4])
			{
				m_DurabilityLv[GameDataManager::DESTROYER] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV4];
				m_CurrentLevel[3]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV5])
			{
				m_DurabilityLv[GameDataManager::DESTROYER] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV5];
				m_CurrentLevel[3]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
	if (m_IsEnhancementFilDrawn[GameDataManager::CRUISER][DURABILITY])
	{
		switch (m_DurabilityLv[GameDataManager::CRUISER])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV1])
			{
				m_DurabilityLv[GameDataManager::CRUISER] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV1];
				m_CurrentLevel[6]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV2])
			{
				m_DurabilityLv[GameDataManager::CRUISER] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV2];
				m_CurrentLevel[6]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV3])
			{
				m_DurabilityLv[GameDataManager::CRUISER] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV3];
				m_CurrentLevel[6]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV4])
			{
				m_DurabilityLv[GameDataManager::CRUISER] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV4];
				m_CurrentLevel[6]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV5])
			{
				m_DurabilityLv[GameDataManager::CRUISER] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV5];
				m_CurrentLevel[6]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
	if (m_IsEnhancementFilDrawn[GameDataManager::BATTLESHIP][DURABILITY])
	{
		switch (m_DurabilityLv[GameDataManager::BATTLESHIP])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV1])
			{
				m_DurabilityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV1];
				m_CurrentLevel[9]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV2])
			{
				m_DurabilityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV2];
				m_CurrentLevel[9]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV3])
			{
				m_DurabilityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV3];
				m_CurrentLevel[9]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV4])
			{
				m_DurabilityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV4];
				m_CurrentLevel[9]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV5])
			{
				m_DurabilityLv[GameDataManager::BATTLESHIP] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV5];
				m_CurrentLevel[9]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
}

void PolicyMenu::SpeedLvUP()
{
	if (m_IsEnhancementFilDrawn[GameDataManager::DESTROYER][SPEED])
	{
		switch (m_SpeedLv[GameDataManager::DESTROYER])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV1])
			{
				m_SpeedLv[GameDataManager::DESTROYER] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV1];
				m_CurrentLevel[5]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV2])
			{
				m_SpeedLv[GameDataManager::DESTROYER] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV2];
				m_CurrentLevel[5]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV3])
			{
				m_SpeedLv[GameDataManager::DESTROYER] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV3];
				m_CurrentLevel[5]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV4])
			{
				m_SpeedLv[GameDataManager::DESTROYER] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV4];
				m_CurrentLevel[5]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV5])
			{
				m_SpeedLv[GameDataManager::DESTROYER] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::DESTROYER][GameDataManager::LV5];
				m_CurrentLevel[5]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
	if (m_IsEnhancementFilDrawn[GameDataManager::CRUISER][SPEED])
	{
		switch (m_SpeedLv[GameDataManager::CRUISER])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV1])
			{
				m_SpeedLv[GameDataManager::CRUISER] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV1];
				m_CurrentLevel[8]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV2])
			{
				m_SpeedLv[GameDataManager::CRUISER] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV2];
				m_CurrentLevel[8]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV3])
			{
				m_SpeedLv[GameDataManager::CRUISER] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV3];
				m_CurrentLevel[8]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV4])
			{
				m_SpeedLv[GameDataManager::CRUISER] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV4];
				m_CurrentLevel[8]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV5])
			{
				m_SpeedLv[GameDataManager::CRUISER] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::CRUISER][GameDataManager::LV5];
				m_CurrentLevel[8]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
	if (m_IsEnhancementFilDrawn[GameDataManager::BATTLESHIP][SPEED])
	{
		switch (m_SpeedLv[GameDataManager::BATTLESHIP])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV1])
			{
				m_SpeedLv[GameDataManager::BATTLESHIP] = GameDataManager::LV2;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV1];
				m_CurrentLevel[11]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV2])
			{
				m_SpeedLv[GameDataManager::BATTLESHIP] = GameDataManager::LV3;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV2];
				m_CurrentLevel[11]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV3])
			{
				m_SpeedLv[GameDataManager::BATTLESHIP] = GameDataManager::LV4;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV3];
				m_CurrentLevel[11]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV4])
			{
				m_SpeedLv[GameDataManager::BATTLESHIP] = GameDataManager::LV5;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV4];
				m_CurrentLevel[11]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV5])
			{
				m_SpeedLv[GameDataManager::BATTLESHIP] = GameDataManager::LV6;
				m_SumMoney += m_EnhancementCost[GameDataManager::BATTLESHIP][GameDataManager::LV5];
				m_CurrentLevel[11]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
}


void PolicyMenu::ExchangeLvUP()
{
	if (m_IsExchangeFilDrawn[IKOKU])
	{
		switch (m_ExchangeLv[IKOKU])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_ExchangeCost[IKOKU][GameDataManager::LV1])
			{
				m_ExchangeLv[IKOKU] = GameDataManager::LV2;
				m_SumMoney += m_ExchangeCost[IKOKU][GameDataManager::LV1];
				m_CurrentLevel[0]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_ExchangeCost[IKOKU][GameDataManager::LV2])
			{
				m_ExchangeLv[IKOKU] = GameDataManager::LV3;
				m_SumMoney += m_ExchangeCost[IKOKU][GameDataManager::LV2];
				m_CurrentLevel[0]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_ExchangeCost[IKOKU][GameDataManager::LV3])
			{
				m_ExchangeLv[IKOKU] = GameDataManager::LV4;
				m_SumMoney += m_ExchangeCost[IKOKU][GameDataManager::LV3];
				m_CurrentLevel[0]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_ExchangeCost[IKOKU][GameDataManager::LV4])
			{
				m_ExchangeLv[IKOKU] = GameDataManager::LV5;
				m_SumMoney += m_ExchangeCost[IKOKU][GameDataManager::LV4];
				m_CurrentLevel[0]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_ExchangeCost[IKOKU][GameDataManager::LV5])
			{
				m_ExchangeLv[IKOKU] = GameDataManager::LV6;
				m_SumMoney += m_ExchangeCost[IKOKU][GameDataManager::LV5];
				m_CurrentLevel[0]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
	if (m_IsExchangeFilDrawn[ROKOKU])
	{
		switch (m_ExchangeLv[ROKOKU])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_ExchangeCost[ROKOKU][GameDataManager::LV1])
			{
				m_ExchangeLv[ROKOKU] = GameDataManager::LV2;
				m_SumMoney += m_ExchangeCost[ROKOKU][GameDataManager::LV1];
				m_CurrentLevel[1]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_ExchangeCost[ROKOKU][GameDataManager::LV2])
			{
				m_ExchangeLv[ROKOKU] = GameDataManager::LV3;
				m_SumMoney += m_ExchangeCost[ROKOKU][GameDataManager::LV2];
				m_CurrentLevel[1]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_ExchangeCost[ROKOKU][GameDataManager::LV3])
			{
				m_ExchangeLv[ROKOKU] = GameDataManager::LV4;
				m_SumMoney += m_ExchangeCost[ROKOKU][GameDataManager::LV3];
				m_CurrentLevel[1]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_ExchangeCost[ROKOKU][GameDataManager::LV4])
			{
				m_ExchangeLv[ROKOKU] = GameDataManager::LV5;
				m_SumMoney += m_ExchangeCost[ROKOKU][GameDataManager::LV4];
				m_CurrentLevel[1]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_ExchangeCost[ROKOKU][GameDataManager::LV5])
			{
				m_ExchangeLv[ROKOKU] = GameDataManager::LV6;
				m_SumMoney += m_ExchangeCost[ROKOKU][GameDataManager::LV5];
				m_CurrentLevel[1]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
	if (m_IsExchangeFilDrawn[HAKOKU])
	{
		switch (m_ExchangeLv[HAKOKU])
		{
		case GameDataManager::LV1:
			if (m_MyMoney >= m_ExchangeCost[HAKOKU][GameDataManager::LV1])
			{
				m_ExchangeLv[HAKOKU] = GameDataManager::LV2;
				m_SumMoney += m_ExchangeCost[HAKOKU][GameDataManager::LV1];
				m_CurrentLevel[2]++;
			}
			break;
		case GameDataManager::LV2:
			if (m_MyMoney >= m_ExchangeCost[HAKOKU][GameDataManager::LV2])
			{
				m_ExchangeLv[HAKOKU] = GameDataManager::LV3;
				m_SumMoney += m_ExchangeCost[HAKOKU][GameDataManager::LV2];
				m_CurrentLevel[2]++;
			}
			break;
		case GameDataManager::LV3:
			if (m_MyMoney >= m_ExchangeCost[HAKOKU][GameDataManager::LV3])
			{
				m_ExchangeLv[HAKOKU] = GameDataManager::LV4;
				m_SumMoney += m_ExchangeCost[HAKOKU][GameDataManager::LV3];
				m_CurrentLevel[2]++;
			}
			break;
		case GameDataManager::LV4:
			if (m_MyMoney >= m_ExchangeCost[HAKOKU][GameDataManager::LV4])
			{
				m_ExchangeLv[HAKOKU] = GameDataManager::LV5;
				m_SumMoney += m_ExchangeCost[HAKOKU][GameDataManager::LV4];
				m_CurrentLevel[2]++;
			}
			break;
		case GameDataManager::LV5:
			if (m_MyMoney >= m_ExchangeCost[HAKOKU][GameDataManager::LV5])
			{
				m_ExchangeLv[HAKOKU] = GameDataManager::LV6;
				m_SumMoney += m_ExchangeCost[HAKOKU][GameDataManager::LV5];
				m_CurrentLevel[2]++;
			}
			break;
		case GameDataManager::LV6:
			break;
		default:
			break;
		}
	}
}
void PolicyMenu::CreatShip()
{
	static int BattleShipPushCount = 0;
	static int CruiserShipPushCount = 0;
	if (m_IsEnhancementFilDrawn[GameDataManager::BATTLESHIP][CREATSHIP])
	{
		if (BattleShipPushCount < 1)
		{
			m_SumMoney += m_CreatShipCost[GameDataManager::BATTLESHIP];
			BattleShipPushCount++;
			m_IsBattleShipSelected = true;
		}
	}

	if (m_IsEnhancementFilDrawn[GameDataManager::CRUISER][CREATSHIP])
	{
		if (CruiserShipPushCount < 1)
		{
			m_SumMoney += m_CreatShipCost[GameDataManager::CRUISER];
			CruiserShipPushCount++;
			m_IsCruiserSelected = true;
		}
	}

	if (m_IsPushCancellationDrawn)
	{
		BattleShipPushCount = 0;
		CruiserShipPushCount = 0;
		m_IsBattleShipSelected = false;
		m_IsCruiserSelected = false;
	}
}