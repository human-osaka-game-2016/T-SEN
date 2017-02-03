/**
* @file PolicyMenu.h
* @brief PolicyMenuクラスヘッダ
* @author matsuda
*/
#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include"PolicyMenu.h"
#include "../../Button/BasicButton.h"
#include "../../Button/ButtonFunction/ButtonFunctionList.h"

namespace
{

	const     DWORD   BrightnessVal = 0x99999999;		// 明度基本値
	const	  DWORD   BrightnessValMax = 0xffffffff;		// 明度最大値
	D3DXVECTOR2 ExchangeLvUpTexPos[PolicyMenu::EXCHANGE_MAX] {{ 100.f, 450.f }, { 100.f, 635.f }, { 100.f, 820.f }, };
	D3DXVECTOR2 EnhancementLvUpTexPos[GameDataManager::SHIP_ID_MAX][PolicyMenu::ENHANCEMENT_MAX]
	{
		{ { 0.0f, 0.0f }, { 410.f, 464.f }, { 410.f, 642.f }, { 410.f, 822.f }, },
		{ { 680.f, 279.f }, { 680.f, 464.f }, { 680.f, 642.f }, { 680.f, 822.f }, },
		{ { 950.f, 279.f }, { 950.f, 464.f }, { 950.f, 642.f }, { 945.f, 822.f } },
	};
}

PolicyMenu::PolicyMenu(GameDataManager* GameDataManager)
	: m_IsPushHomeDrawn(false)
	, m_IsPushSettlementDrawn(false)
	, m_IsPushCancellationDrawn(false)
{
	D3DXVECTOR2 HomeBtnPos{ 160.f, 100.f };
	m_pHomeButton = new ScaleFunction(new BasicButton(HomeBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::HOME_BUTTON_VTX));
	m_pPushHomeButton = new ScaleFunction(new BasicButton(HomeBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::HOME_PUSH_BUTTON_VTX));

	D3DXVECTOR2 SettlementBtnPos{1270.f,770.f};
	m_pSettlementButton = new ScaleFunction(new BasicButton(SettlementBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SETTLEMENT_BUTTON_VTX));
	m_pPushSettlementButton = new ScaleFunction(new BasicButton(SettlementBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::SETTLEMENT_PUSH_BUTTON_VTX));

	D3DXVECTOR2 CancellationBtnPos{1490.f,765.f};
	m_pCancellationButton = new ScaleFunction(new BasicButton(CancellationBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::CANCELLATION_BUTTON_VTX));
	m_pPushCancellationButton = new ScaleFunction(new BasicButton(CancellationBtnPos, sub_scene::Policy::POLICY_TEX, sub_scene::Policy::CANCELLATION_PUSH_BUTTON_VTX));

	D3DXVECTOR2 EnhancementFilterBtnPos[GameDataManager::SHIP_ID_MAX][ENHANCEMENT_MAX]
	{
		{ { 1.0f, 1.0f }, { 470.f, 412.f }, { 470.f, 592.f }, { 470.f, 772.f }, },
		{ { 740.f, 227.f }, { 740.f, 412.f }, { 740.f, 592.f }, { 740.f, 772.f }, },
		{ { 1010.f, 227.f }, { 1010.f, 412.f }, { 1010.f, 592.f }, { 1010.f, 772.f }, },
	};

	D3DXVECTOR2 ExchangeFilterBtnPos[EXCHANGE_MAX]
	{
		{160.f,405.f},
		{160.f,590.f},
		{160.f,775.f},
	};

	for (int i = 0; i < GameDataManager::SHIP_ID_MAX; i++)
	{
		for (int j = 0; j < ENHANCEMENT_MAX; j++)
		{
			m_pEnhancementFilterButton[i][j] = new ScaleFunction(new BasicButton(EnhancementFilterBtnPos[i][j], sub_scene::Policy::POLICY_TEX, sub_scene::Policy::ENHANCEMENT_FILTER_VTX));
		}
	}

	for (int i = 0; i < EXCHANGE_MAX; i++)
	{
		m_pExchangeFilterButton[i] = new ScaleFunction(new BasicButton(ExchangeFilterBtnPos[i], sub_scene::Policy::POLICY_TEX, sub_scene::Policy::EXCHANGE_FILTER_VTX));
	}

	m_EnhancementTexPos = { 740.f, 450.f };
	m_ExchangeTexPos = { 160.f, 540.f };
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

}

PolicyMenu::~PolicyMenu()
{
	delete m_pHomeButton;
	delete m_pPushHomeButton;
	delete m_pSettlementButton;
	delete m_pPushSettlementButton;
	delete m_pCancellationButton;
	delete m_pPushCancellationButton;

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
}

sub_scene::SUBSCENE_ID PolicyMenu::Control()
{
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
					m_IsEnhancementFilDrawn[i][j] = false;
				}
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
			else if (GameLib::Instance().ChecKMouseL() == OFF && m_IsEnhancementFilDrawn)
			{
				m_IsExchangeFilDrawn[i] = false;
			}
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

	//強化でのPush時のフィルター描画
	for (int i = 0; i < GameDataManager::SHIP_ID_MAX; i++)
	{
		for (int j = 0; j < ENHANCEMENT_MAX; j++)
		{
			GameLib::Instance().DrawXYCenterPos(sub_scene::Policy::LVUP_TEX, sub_scene::Policy::LVUP_VTX, EnhancementLvUpTexPos[i][j].x, EnhancementLvUpTexPos[i][j].y);
			if (m_IsEnhancementFilDrawn[i][j])
			{
				m_pEnhancementFilterButton[i][j]->Draw();
			}
		}
	}
	//交流でのPush時のフィルター描画
	for (int i = 0; i < EXCHANGE_MAX; i++)
	{
		GameLib::Instance().DrawXYCenterPos(sub_scene::Policy::LVUP_TEX, sub_scene::Policy::LVUP_VTX, ExchangeLvUpTexPos[i].x, ExchangeLvUpTexPos[i].y);
		if (m_IsExchangeFilDrawn[i])
		{
			m_pExchangeFilterButton[i]->Draw();
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