/**
* @file BattleResult.cpp
* @brief BattlerResultクラス実装
* @author haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include "../../GameData/GameTimer.h"
#include "../../GameData/SaveDataManager.h"
#include "BattleResult.h"
#include "ScoreResult.h"
#include "ResultBackground.h"
#include "../../Message/GameMessage.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//-------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

const	D3DXVECTOR2		MessagePos		= {250.f, 800.f};		// メッセージ位置座標
const	INT				MessageScale	= 50;					// メッセージの大きさ

}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Namespace sub_scene
//-------------------------------------------------------------------------------------------------------------------------------------//

namespace sub_scene
{

//--------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------//

BattleResult::BattleResult(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager)
	: SubScene(pGameDataManager, pGameTimer, pSaveDataManager)
	, m_pScoreResult(new ScoreResult(pGameDataManager))
	, m_pBackground(new ResultBackground(RESULT_TEX, RESULT_VTX))
	, m_pMessage(new GameMessage(MessagePos, "空白釦を押してください", MessageScale))
	, m_State(RESULT_FEDE_IN)
{
	/**@todo 勝敗結果によって読み込むテクスチャーを変える予定。現在は仕組みがないため未実装*/
	m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/ResultScene/resultVictory.png");
	//m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/ResultScene/resultLose.png");
	//m_rGameLib.LoadTex(RESULT_TEX, "../Resouce/ResultScene/result.png");
}


BattleResult::~BattleResult()
{
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
			m_State = SCORE_DISP;
		}

		if(m_rGameLib.CheckKey(DIK_SPACE, SPACE) == ON)
		{
			m_pBackground->EndFedeIn();
			m_State = SCORE_DISP;
		}
		break;

	case SCORE_DISP:
		if(m_rGameLib.CheckKey(DIK_SPACE, SPACE) == PUSH)
		{
			return SUBSCENE_ID::HOME;
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

	case SCORE_DISP:
		m_pScoreResult->Draw();
		m_pMessage->Draw();
		break;

	default:
		// do nothing
		break;
	}
}

}
