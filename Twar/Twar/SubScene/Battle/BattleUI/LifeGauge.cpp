/**
* @file LifeGauge.cpp
* @brief LifeGaugeのクラス実装
* @author ichikawa
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "LifeGauge.h"
#include "../BattleData/BattleDataManager.h"


//
namespace
{
	const float LifePosY = 785.f;
}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

LifeGauge::LifeGauge(int lifeTexID, int lifeVtxID, int flameVtxID, int MosterflameID)
	: m_LifeTv(0.0f)
	, m_LifeTu()
	, m_LifeHeight(450.f)
{
	m_LifeMAX = BattleDataManager::Instance().GetPlayerHp();
	CurrentLife = m_LifeMAX;
	m_LifeTvCount = 1.0f / m_LifeMAX;
	m_LifePos.x = 45.f;
	m_LifePos.y = LifePosY;
	m_LifePosCount = 400.f / m_LifeMAX;
	m_Pos.x = 45.0f;
	m_Pos.y = LifePosY;
	m_TexID[UI] = lifeTexID;
	//m_TexID[FLAME] = flameTexID;
	//m_TexID[DECORATION] = decoTexID;
	m_VtxID = lifeVtxID;
	m_FlameVtxID = flameVtxID;
	m_MonsterFlameID = MosterflameID;
	GameLib::Instance().CreateVtx(m_VtxID, 450.f, 100.f);
	GameLib::Instance().CreateVtx(m_FlameVtxID, 450.f, 100.f);
	GameLib::Instance().CreateVtx(m_MonsterFlameID, 450.f, 100.f);
}

LifeGauge::~LifeGauge()
{
	// リソースはManagerで解放
}

void LifeGauge::Control()
{
	CurrentLife = BattleDataManager::Instance().GetPlayerHp();

	if (m_LifeMAX != CurrentLife)
	{

		m_LifeTu += (m_LifeMAX - CurrentLife) * m_LifeTvCount;	//ダメージ表示分
		m_LifePos.x += ((m_LifeMAX - CurrentLife) * m_LifePosCount) / 1.0f;	//ダメージ表示分
		m_LifeHeight -= (m_LifeMAX - CurrentLife) * m_LifePosCount;;	//ダメージ計算
		m_LifeMAX = CurrentLife;	//ダメージ計算

	}
}

void LifeGauge::Draw()
{
	GameLib::Instance().SetVtxUV(m_VtxID, 130 / 1024.f, 580 / 1024.f, m_LifeTv, 100 / 512.f);
	GameLib::Instance().SetVtxSize(m_VtxID, m_LifeHeight, 100.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_VtxID, m_LifePos.x, m_LifePos.y);

	GameLib::Instance().SetVtxUV(m_FlameVtxID, 130.f / 1024.f, 580.f / 1024.f, 200.f / 512.f, 300.f / 512.f);
	GameLib::Instance().SetVtxColor(m_FlameVtxID, 0xffffffff);
	GameLib::Instance().DrawXY(m_TexID[UI], m_FlameVtxID, m_Pos.x, m_Pos.y);

}
