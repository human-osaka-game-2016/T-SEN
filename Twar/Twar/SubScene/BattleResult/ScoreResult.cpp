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

const INT				FontHeight				= 50;							// 1文字の大きさ(縦幅)
const INT				FontWidth				= 50;							// 1文字の大きさ(横幅)
const D3DXVECTOR2		FontPos					= { 200.f, 100.f };				// 表示位置座標
const D3DXVECTOR2		FontPos2				= { 200.f, 300.f };				// 表示位置座標2
const D3DXVECTOR2		FontPos3				= { 200.f, 500.f };				// 表示位置座標3
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
	std::string str1 ="与ダメージ : " + std::to_string(m_Data[PLAYER_DAMAGE_SCORE]) + "\n";
	m_pFont->Draw(str1.c_str(), FontPos);

	std::string str2 = "経過日数 : " + std::to_string(m_Data[ELAPSED_DAYS]) + "\n";
	m_pFont->Draw(str2.c_str(), FontPos2);

	std::string str3 = "取得した通貨 : " + std::to_string(m_Data[GETTEN_MONEY]) + "\n";
	m_pFont->Draw(str3.c_str(), FontPos3);
}

//--------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------//

void ScoreResult::InitData()
{
	m_Data[PLAYER_DAMAGE_SCORE] = m_pGameDataManager->GetMoney();
	m_Data[ELAPSED_DAYS] = BattleDataManager::Instance().GetPlayerAttackDamage();
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
		int correctionVal = 0;
		int fightOffDay = m_pGameDataManager->GetFightOffDays();

		// caseの数値は日数。モンスターが出現して3日内に撃退すれば補正値が入る
		switch(fightOffDay)
		{
		case 10:
			correctionVal = 30;
			break;

		case 9:
			correctionVal = 20;
			break;

		case 8:
			correctionVal = 10;
			break;

		default:
			// 出現してから4日目以降は補正値ははいらない
			break;
		}

		gettenMoney += correctionVal;
	}

	// 与ダメージ補正
	{
		int correctionVal = 0;

		// モンスターへのダメージ倍率
		int playerAttackDamage  = BattleDataManager::Instance().GetPlayerAttackDamage();
		int monsterHpMax = BattleDataManager::Instance().GetMonsterHpMax();
		float damageMagnification = 0.0f;
		damageMagnification = static_cast<float>(playerAttackDamage) / static_cast<float>(monsterHpMax);


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
