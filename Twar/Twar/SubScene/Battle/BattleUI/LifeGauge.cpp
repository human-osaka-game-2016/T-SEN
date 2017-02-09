//==================================================================================================================================//
//!< @file		LifeGauge.cpp
//!< @brief		LifeGaugeクラス実装
//!< @author	ichikawa
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Include
//--------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "LifeGauge.h"
#include "../BattleData/BattleDataManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const float LifePosY = 700.f;

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

LifeGauge::LifeGauge(int lifeTexID, int flameTexID, int decoTexID, int lifeVtxID, int flameVtxID)
	: m_LifeTv(0.0f)
	, m_LifeHeight(400.f)
{
	//m_LifeMAX = BattleStateManager::Instance().GetPlayerHp();
	CurrentLife = m_LifeMAX;
	m_LifeTvCount = 1.0f / m_LifeMAX;
	m_LifePos.x = 50.f;
	m_LifePos.y = LifePosY;
	m_LifePosCount = 400.f / m_LifeMAX;
	m_Pos.x = 50.0f;
	m_Pos.y = LifePosY;
	m_TexID[LIFE] = lifeTexID;
	m_TexID[FLAME] = flameTexID;
	m_TexID[DECORATION] = decoTexID;
	m_VtxID = lifeVtxID;
	m_FlameVtxID = flameVtxID;
	GameLib::Instance().CreateVtx(m_VtxID, 100.f, 400.f);
	GameLib::Instance().CreateVtx(m_FlameVtxID, 100.f, 400.f);
}

LifeGauge::~LifeGauge()
{
	// リソースはManagerで解放
}

void LifeGauge::Control()
{

	if(m_LifeMAX != CurrentLife)
	{

		m_LifeTv += (m_LifeMAX - CurrentLife) * m_LifeTvCount;
		m_LifePos.y += ((m_LifeMAX - CurrentLife) * m_LifePosCount) / 2.0f;
		m_LifeHeight -= (m_LifeMAX - CurrentLife) * m_LifePosCount;;
		m_LifeMAX = CurrentLife;

	}
}

void LifeGauge::Draw()
{
	GameLib::Instance().SetVtxUV(m_VtxID, 0.0f, 1.0f, m_LifeTv, 1.0f);
	GameLib::Instance().SetVtxSize(m_VtxID, 100.0f, m_LifeHeight);
	GameLib::Instance().DrawXYCenterPos(m_TexID[LIFE], m_VtxID, m_LifePos.x, m_LifePos.y);
	GameLib::Instance().DrawXYCenterPos(m_TexID[FLAME], m_FlameVtxID, m_Pos.x, m_Pos.y);
	GameLib::Instance().DrawXYCenterPos(m_TexID[DECORATION], m_FlameVtxID, m_Pos.x, m_Pos.y);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//

