/**
* @file BattleUIManager.cpp
* @brief BattleUIManagerクラス実装
* @author ichikawa
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "Gamelib/GameLib.h"
#include "../Battle.h"
#include "BattleUIManager.h"
#include "UI.h"
#include "LifeGauge.h"
#include "SpeedMeter.h"
#include "MonsterLifeGauge.h"
#include "Alignment.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

BattleUIManager::BattleUIManager()
{
	InitData();
	m_pUI.emplace_back(new LifeGauge(sub_scene::Battle::UI, sub_scene::Battle::MONSTER_LIFE_GAUGE, sub_scene::Battle::MONSTER_FLAME, sub_scene::Battle::MONSTER_BASE));
	m_pUI.emplace_back(new SpeedMeter(sub_scene::Battle::UI, sub_scene::Battle::METER, sub_scene::Battle::AICON));
	m_pUI.emplace_back(new MonsterLifeGauge(sub_scene::Battle::UI, sub_scene::Battle::MONSTER_BASE, sub_scene::Battle::MONSTER_FLAME));
	m_pUI.emplace_back(new Alignment(sub_scene::Battle::ALIGNMENT, sub_scene::Battle::ALIGNMENTZOOM, sub_scene::Battle::ALIGNMENT_VTX));
}

BattleUIManager::~BattleUIManager()
{
	for (auto i : m_pUI)
	{
		delete i;
	}
	m_pUI.clear();
}

void BattleUIManager::Control()
{
	for (auto itr = m_pUI.begin(); itr != m_pUI.end(); ++itr)
	{
		(*itr)->Control();
	}
}

void BattleUIManager::Draw()
{
	GameLib::Instance().GetDevice()->SetFVF(DIRECT3DFVF_CUSTOMVERTEX);

	for (auto itr = m_pUI.begin(); itr != m_pUI.end(); ++itr)
	{
		(*itr)->Draw();
	}

	GameLib::Instance().GetDevice()->SetFVF(USER_VERTEX_FVF);
}

//------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//------------------------------------------------------------------------------------------------------------------------------------//

void BattleUIManager::InitData()
{
	//GameLib::Instance().LoadTexEx(sub_scene::Battle::LIFE,"../Resouce/LIFE.png", 255, 0, 0, 0, false);
	//GameLib::Instance().LoadTexEx(sub_scene::Battle::LIFE_FLAME, "../Resouce/LIFE_FLAME.png", 255, 0, 0, 0, false);
	//GameLib::Instance().LoadTexEx(sub_scene::Battle::LIFE_DECORATION, "../Resouce/LIFE_DECO.png", 255, 0, 0, 0, false);
	//
	//GameLib::Instance().LoadTexEx(sub_scene::Battle::METER_BG, "../Resouce/SPEED_BG.png", 255, 0, 0, 0, false);
	//GameLib::Instance().LoadTexEx(sub_scene::Battle::METER_DIAL, "../Resouce/SPEED_FLAME.png", 255, 0, 0, 0, false);
	//GameLib::Instance().LoadTexEx(sub_scene::Battle::METER_NEEDLE, "../Resouce/SPEED_NEEDLE.png", 255, 0, 0, 0, false);
	//GameLib::Instance().LoadTex(sub_scene::Battle::METER_AICON, "../Resouce/aikon.png");

	GameLib::Instance().LoadTexEx(sub_scene::Battle::ALIGNMENT, "../Resouce/BattleScene/UI/Alignment.png", 255, 0, 0, 0, false);
	GameLib::Instance().LoadTexEx(sub_scene::Battle::ALIGNMENTZOOM, "../Resouce/BattleScene/UI/AlignmentZoom.png", 255, 255, 0, 0, false);
	GameLib::Instance().LoadTexEx(sub_scene::Battle::UI, "../Resouce/BattleScene/UI/sento_ui_0.png", 255, 255, 0, 0, false);
}
