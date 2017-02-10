/**
* @file MnsterLifeGauge.cpp
* @brief MnsterLifeGaugeのクラス実装
* @author ichikawa
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "MonsterLifeGauge.h"
#include "../BattleData/BattleDataManager.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

	const float			LifePosX = 1115.f;
	const D3DXVECTOR2	Pos = { 1115.f, 40.f };
	const float			VtxHeight = 100.f;
	const float			VtxWidth = 450.f;

}

//--------------------------------------------------------------------------------------------------------------------------------------//
//public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

MonsterLifeGauge::MonsterLifeGauge(int lifeTexID, int LifeVtrID, int FlameVtrID)
	: m_LifeTv(0.0f)
	, m_LifeTu(130.f / 1024.f)
	, m_LifeHeight(100.f)
	, m_LifeWide(450.f)
{
	m_Angle = 90.f;
	m_LifeMAX = BattleDataManager::Instance().GetMonsterHp();
	m_CurrentLife = m_LifeMAX;
	m_LifeTvCount = 1.0f / m_LifeMAX;
	m_LifePos = Pos;
	m_LifeFlamePos = Pos;
	m_LifePosCount = VtxWidth / m_LifeMAX;
	m_Pos = Pos;

	m_TexID[UI] = lifeTexID;
	m_LifeFlameID = FlameVtrID;
	GameLib::Instance().CreateVtx(m_LifeFlameID, 450.f, 100.f);
	m_LifeID = LifeVtrID;
	GameLib::Instance().CreateVtx(m_LifeID, 450.f, 100.f);
	m_LifeBaseID = FlameVtrID;
	GameLib::Instance().CreateVtx(m_LifeBaseID, 450.f, 100.f);
}

MonsterLifeGauge::~MonsterLifeGauge()
{
}

void MonsterLifeGauge::Control()
{
	m_CurrentLife = BattleDataManager::Instance().GetMonsterHp();
}

void MonsterLifeGauge::Draw()
{
	// ライフゲージ
	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().SetVtxUV(m_LifeID, m_LifeTu, (130.f + VtxWidth) / 1024.f, 100.f / 512.f, (100.f + VtxHeight) / 512.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_LifeID, m_LifePos.x, m_LifePos.y);

	// フレーム描画
	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().SetVtxUV(m_LifeFlameID, 130.f / 1024.f, 580.f / 1024.f, 200.f / 512.f, 300.f / 512.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_LifeFlameID, m_LifeFlamePos.x, m_LifeFlamePos.y);
}
