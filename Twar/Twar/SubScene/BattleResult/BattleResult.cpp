//==================================================================================================================================//
//!< @file		BattleResult.cpp
//!< @brief		BattlerResultクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include "../../GameData/GameTimer.h"
#include "../../GameData/SaveDataManager.h"
#include "BattleResult.h"
#include "ScoreResult.h"
#include "ResultBackground.h"
#include "../../Message/GameMessage.h"
#include "../Battle/BattleData/BattleDataManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const	D3DXVECTOR2		MessagePos		= {250.f, 800.f};		// メッセージ位置座標
const	INT				MessageScale	= 50;					// メッセージの大きさ
const	int				WaveCountMax	= 3;					// ウェーブカウントの最大値
const	int				SceneChangeTime = 300;					// シーンが切り替わる時間

}

//--------------------------------------------------------------------------------------------------------------//
//Namespace sub_scene
//--------------------------------------------------------------------------------------------------------------//

namespace sub_scene
{

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

BattleResult::BattleResult(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	: SubScene(pGameDataManager, pGameTimer, pSaveDataManager)
	, m_pGameDataManager(pGameDataManager)
	, m_pScoreResult(new ScoreResult(pGameDataManager))
	, m_pBackground(new ResultBackground(RESULT_TEX, RESULT_VTX))
	, m_pMessage(new GameMessage(MessagePos, "空白釦を押してください", MessageScale))
	, m_State(RESULT_FEDE_IN)
	, m_SceneChangeTimeCount(0)
{
	if(BattleDataManager::Instance().GetBattleResult())
	{
		m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/ResultScene/resultVictory.png");
		m_pGameDataManager->ResetWaveData();
	}
	else
	{
		m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/ResultScene/resultLose.png");
		int fightOffDay = m_pGameDataManager->GetFightOffDays();
		--fightOffDay;
		m_pGameDataManager->SetFightOffDays(fightOffDay);
	}

	//m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/ResultScene/result.png");
}


BattleResult::~BattleResult()
{
	m_rGameLib.ReleaseAllTex();
	m_rGameLib.ReleaseAllVertex();
	delete m_pMessage;
	delete m_pBackground;
	delete m_pScoreResult;
}

SUBSCENE_ID BattleResult::Control()
{
	switch(m_State)
	{
	case RESULT_FEDE_IN:
		if(m_pBackground->Control())
		{
			if(m_pGameDataManager->GetWaveCount() > WaveCountMax || m_pGameDataManager->GetFightOffDays() <= 0)
			{
				m_State = SCORE_DISP_RETURN_ENDROLL;
			}
			else
			{
				m_State = SCORE_DISP_RETURN_HOME;
			}
			m_pGameDataManager->SetMoney(m_pScoreResult->GetMoneyData());
		}

		if(m_rGameLib.CheckKey(DIK_SPACE, SPACE) == ON)
		{
			if(m_pGameDataManager->GetWaveCount() > WaveCountMax || m_pGameDataManager->GetFightOffDays() <= 0)
			{
				m_State = SCORE_DISP_RETURN_ENDROLL;
			}
			else
			{
				m_State = SCORE_DISP_RETURN_HOME;
			}
			m_pBackground->EndFedeIn();
		}
		break;

	case SCORE_DISP_RETURN_HOME:
		if(m_rGameLib.CheckKey(DIK_SPACE, SPACE) == PUSH)
		{
			return SUBSCENE_ID::HOME;
		}
		break;

	case SCORE_DISP_RETURN_ENDROLL:

		++m_SceneChangeTimeCount;
		if(m_SceneChangeTimeCount >= SceneChangeTime)
		{
			if(m_pGameDataManager->GetWaveCount() > WaveCountMax)
			{
				return SUBSCENE_ID::GAME_CLEAR;
			}
			else if(m_pGameDataManager->GetFightOffDays() <= 0)
			{
				return SUBSCENE_ID::GAME_OVER;
			}
		}
		break;

	default:
		// do nothing
		break;
	}

	return SUBSCENE_ID::BATTLE_RESULT;
}

void BattleResult::Draw()
{
	m_pBackground->Draw();
	switch(m_State)
	{
	case RESULT_FEDE_IN:
		break;

	case SCORE_DISP_RETURN_HOME:
		m_pScoreResult->Draw();
		m_pMessage->Draw();
		break;

	case SCORE_DISP_RETURN_ENDROLL:
		m_pScoreResult->Draw();
		break;

	default:
		// do nothing
		break;
	}
}

}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
