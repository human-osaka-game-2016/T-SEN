//==================================================================================================================================//
//!< @file		BattleUIManager.cpp
//!< @brief		BattleUIManagerクラス実装
//!< @author	ichikawa
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "Gamelib/GameLib.h"
#include "../Battle.h"
#include "BattleUIManager.h"
#include "UI.h"
#include "LifeGauge.h"
#include "SpeedMeter.h"
#include "MonsterLifeGauge.h"
#include "Alignment.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

BattleUIManager::BattleUIManager()
{
	InitData();
	//m_pUI.emplace_back(new LifeGauge(sub_scene::Battle::LIFE, sub_scene::Battle::LIFE_FLAME, sub_scene::Battle::LIFE_DECORATION, sub_scene::Battle::LIFE_GAUGE, sub_scene::Battle::LIFE_DECO_FLAME));
	//m_pUI.emplace_back(new SpeedMeter(sub_scene::Battle::METER_BG, sub_scene::Battle::METER_DIAL, sub_scene::Battle::METER_NEEDLE, sub_scene::Battle::METER));
	//m_pUI.emplace_back(new MonsterLifeGauge(sub_scene::Battle::LIFE, sub_scene::Battle::LIFE_FLAME));
	//m_pUI.emplace_back(new Alignment(sub_scene::Battle::ALIGNMENT, sub_scene::Battle::ALIGNMENTZOOM, sub_scene::Battle::ALIGNMENT_VTX));
}

BattleUIManager::~BattleUIManager()
{
	for(auto i : m_pUI)
	{
		delete i;
	}
	m_pUI.clear();
}

void BattleUIManager::Control()
{
	for(auto itr = m_pUI.begin(); itr != m_pUI.end(); ++itr)
	{
		(*itr)->Control();
	}
}

void BattleUIManager::Draw()
{
	GameLib::Instance().GetDevice()->SetFVF(DIRECT3DFVF_CUSTOMVERTEX);

	for(auto itr = m_pUI.begin(); itr != m_pUI.end(); ++itr)
	{
		(*itr)->Draw();
	}

	GameLib::Instance().GetDevice()->SetFVF(USER_VERTEX_FVF);
}

//--------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------//

void BattleUIManager::InitData()
{
}
//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
