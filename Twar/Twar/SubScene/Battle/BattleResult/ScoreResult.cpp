/**
* @file		ScoreResult.cpp
* @brief	ScoreResultクラス実装
* @auhtor	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include <string>
#include "ScoreResult.h"
#include "GameLib/GameLib.h"
#include "Font/Font.h"
#include "../../../GameData/GameDataManager.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//-------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

const INT				FontHeight			= 70;							// 1文字の大きさ(縦幅)
const INT				FontWidth			= 70;							// 1文字の大きさ(横幅)
const D3DXVECTOR2		FontPos				= { 200.f, 100.f };				// 表示位置座標

}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

ScoreResult::ScoreResult(GameDataManager* pGameDayaManagher)
	: m_pFont(new Font(GameLib::Instance().GetDevice(), FontHeight, FontWidth))
	, m_pGameDataManager(pGameDayaManagher)
{
	InitData(pGameDayaManagher);
}

ScoreResult::~ScoreResult()
{
	delete m_pFont;
}

void ScoreResult::Draw()
{
	std::string str =
		"BattleScore : " + std::to_string(m_Data[BATTLE_SCORE]) + "\n" +
		"BattleTime  : " + std::to_string(m_Data[BATTLE_TIME]) + "\n";
	m_pFont->Draw(str.c_str(), FontPos);
}

void ScoreResult::PayControl()
{
	m_Data[BATTLE_SCORE] += 10000;
}

int ScoreResult::GetMoneyData()
{
	return m_Data[BATTLE_SCORE];
}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------------------------------//

void ScoreResult::InitData(GameDataManager* pGameDayaManagher)
{
	/**@todo 本来ならGameDataManagerによって値が入るが、現在は未実装の為0で初期化*/
	m_Data[BATTLE_SCORE] = m_pGameDataManager->GetMoney();
	m_Data[BATTLE_TIME] = 0;
}

