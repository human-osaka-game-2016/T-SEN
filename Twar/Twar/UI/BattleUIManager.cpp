//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "Gamelib/GameLib.h"
#include "../SubScene/Battle.h"
#include "BattleUIManager.h"
#include "UI.h"
#include "LifeGauge.h"
#include "SpeedMeter.h"
#include "MonsterLifeGauge.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

BattleUIManager::BattleUIManager()
{
	InitData();
	m_pUI.emplace_back(new LifeGauge(sub_scene::Battle::LIFE, sub_scene::Battle::LIFE_FLAME, sub_scene::Battle::LIFE_DECORATION, sub_scene::Battle::LIFE_GAUGE, sub_scene::Battle::LIFE_DECO_FLAME));
	m_pUI.emplace_back(new SpeedMeter(sub_scene::Battle::METER_BG, sub_scene::Battle::METER_DIAL, sub_scene::Battle::METER_NEEDLE, sub_scene::Battle::METER));
	m_pUI.emplace_back(new MonsterLifeGauge(sub_scene::Battle::LIFE, sub_scene::Battle::LIFE_FLAME));
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

//------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//------------------------------------------------------------------------------------------------------------------------------------//

void BattleUIManager::InitData()
{
	GameLib::Instance().LoadTexEx(sub_scene::Battle::LIFE,"../Resouce/LIFE.png", 255, 0, 0, 0, false);
	GameLib::Instance().LoadTexEx(sub_scene::Battle::LIFE_FLAME, "../Resouce/LIFE_FLAME.png", 255, 0, 0, 0, false);
	GameLib::Instance().LoadTexEx(sub_scene::Battle::LIFE_DECORATION, "../Resouce/LIFE_DECO.png", 255, 0, 0, 0, false);

	GameLib::Instance().LoadTexEx(sub_scene::Battle::METER_BG, "../Resouce/SPEED_BG.png", 255, 0, 0, 0, false);
	GameLib::Instance().LoadTexEx(sub_scene::Battle::METER_DIAL, "../Resouce/SPEED_FLAME.png", 255, 0, 0, 0, false);
	GameLib::Instance().LoadTexEx(sub_scene::Battle::METER_NEEDLE, "../Resouce/SPEED_NEEDLE.png", 255, 0, 0, 0, false);
}
