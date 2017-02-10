/**
* @file SpeedMeter.cpp
* @brief SpeedMeterのクラス実装
* @author ichikawa
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "SpeedMeter.h"
#include "../BattleData/BattleDataManager.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//-------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

	const D3DXVECTOR2		MeterPos = { 100.f, 450.f };
	const float				MinTu = 0.37f;
	const float				MinTV = 0.3f;
	const float				SpeedLimit = 2.f;

	const float				SpeedMeter = 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

SpeedMeter::SpeedMeter(int aiconTexID, int meterVtxID, int MeaterID)
	: m_SpeedMeterPos({ 130.f, 296.f })
	, m_AiconPos({ 53.f, 596.f })
{
	m_PosY = 0.0f;
	m_Pos = MeterPos;
	m_CurrentSpeed = BattleDataManager::Instance().GetPlayerSpeed();
	m_SpeedCount = 148.f / BattleDataManager::Instance().GetSpeedLimit();
	m_Angle = 0.0f;
	m_TexID[UI] = aiconTexID;
	m_AICON_ID = meterVtxID;
	m_SpeedMeterID = MeaterID;
	m_SpeedLimit = 120.f / SpeedLimit;
	GameLib::Instance().CreateVtx(m_AICON_ID, 33.f, 50.f);
	GameLib::Instance().CreateVtx(m_SpeedMeterID, 85.f, 296.f);
}

SpeedMeter::~SpeedMeter()
{
}

void SpeedMeter::Control()

{
	m_CurrentSpeed = BattleDataManager::Instance().GetPlayerSpeed();

	m_PosY = m_CurrentSpeed * m_SpeedCount;
}

void SpeedMeter::Draw()
{
	GameLib::Instance().SetVtxUV(m_AICON_ID, 580.f / 1024.f, 613.f / 1024.f, 0.f / 512.f, 50.f / 512.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_AICON_ID, m_AiconPos.x, (m_AiconPos.y - m_PosY));
	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, speedmeter, sizeof(CUSTOMVERTEX));
	
	for (int i = 0; i < 4; i++)
	{
		aicon[i].x += m_AiconPos.x;
		aicon[i].y += m_AiconPos.y;
	}

	GameLib::Instance().SetVtxUV(m_SpeedMeterID, 0.f / 1024.f, 130.f / 1024.f, 0.f / 512.f, 296.f / 512.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_SpeedMeterID, m_Pos.x, m_Pos.y);

	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, aicon, sizeof(CUSTOMVERTEX));
	/*===================================================for文で座標を減加算する======================================*/


	/*================================================================================================================*/

}
