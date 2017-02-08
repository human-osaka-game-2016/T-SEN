//==================================================================================================================================//
//!< @file		ScoreResult.cpp
//!< @brief		ScoreResultクラス実装
//!< @auhtor	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <string>
#include "ScoreResult.h"
#include "GameLib/GameLib.h"
#include "Font/Font.h"
#include "../../GameData/GameDataManager.h"
#include "../Battle/BattleData/BattleDataManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const INT				FontHeight				= 70;							// 1文字の大きさ(縦幅)
const INT				FontWidth				= 80;							// 1文字の大きさ(横幅)
const D3DXVECTOR2		FontPos					= { 200.f, 100.f };				// 表示位置座標
const int				MoneyCorrectionVal		= 10;							// 通貨補正値(仮)
const int				VictoryCorrectionVal	= 10;							// 勝利した場合におけるお金の補正値
const int				MoneyCorrectionMultiple = 2;							// 補正倍数

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

ScoreResult::ScoreResult(GameDataManager* pGameDayaManagher)
	: m_pFont(new Font(GameLib::Instance().GetDevice(), FontHeight, FontWidth))
	, m_pGameDataManager(pGameDayaManagher)
{
	InitData();
}

ScoreResult::~ScoreResult()
{
	delete m_pFont;
	m_pFont = nullptr;
}

void ScoreResult::Draw()
{
	std::string str =
		"プレイヤーがモンスターに与えたダメージ : " + std::to_string(m_Data[PLAYER_DAMAGE_SCORE]) + "\n" +
		"経過日数								: " + std::to_string(m_Data[ELAPSED_DAYS]) + "\n" +
		"取得した通貨							: " + std::to_string(m_Data[GETTEN_MONEY]) + "\n";
	m_pFont->Draw(str.c_str(), FontPos);
}

//--------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------//

void ScoreResult::InitData()
{
	m_Data[PLAYER_DAMAGE_SCORE] = m_pGameDataManager->GetMoney();
	m_Data[ELAPSED_DAYS] = BattleDataManager::Instance().GetPlayerAttackDamege();
	m_Data[GETTEN_MONEY] = CalculateGettenMoney();
}

int ScoreResult::CalculateGettenMoney()
{
	int gettenMoney = 0;

	// 撃退成功補正
	{
		int correctionMultiple = 1;
		for(char i = 0; i < m_pGameDataManager->GetWaveCount(); ++i)
		{
			// ウェーブ数に応じて2倍ずつしていく
			correctionMultiple *= MoneyCorrectionMultiple;
		}
		gettenMoney += (VictoryCorrectionVal * correctionMultiple);
	}

	// 撃退日数補正
	{
		/**@todo 仕様においてわからない点があるため未実装*/
	}

	// 与ダメージ補正
	{
		int correctionVal = 0;

		// モンスターへのダメージ倍率
		float damageMagnification = static_cast<float>(BattleDataManager::Instance().GetMonsterHp() / BattleDataManager::Instance().GetMonsterHpMax());

		if(damageMagnification < 0.1f)
		{
			// 処理なし
		}
		else if(damageMagnification >= 0.1f && damageMagnification < 0.2f)
		{
			correctionVal = 1;
		}
		else if(damageMagnification >= 0.2f && damageMagnification < 0.3f)
		{
			correctionVal = 2;
		}
		else if(damageMagnification >= 0.3f && damageMagnification < 0.4f)
		{
			correctionVal = 3;
		}
		else if(damageMagnification >= 0.4f && damageMagnification < 0.5f)
		{
			correctionVal = 4;
		}
		else
		{
			correctionVal = 5;
		}

		int correctionMultiple = 1;
		for(char i = 0; i < m_pGameDataManager->GetWaveCount(); ++i)
		{
			// ウェーブ数に応じて2倍ずつしていく
			correctionMultiple *= MoneyCorrectionMultiple;
		}

		gettenMoney += (correctionVal * correctionMultiple);

	}

	// 最後に補正値をかける
	gettenMoney *= MoneyCorrectionVal;

	return gettenMoney;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
