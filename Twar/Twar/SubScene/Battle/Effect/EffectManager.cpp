/**
* @file		EffectManager.cpp
* @brief	EffectManagerクラス実装
* @author	haga
* @todo		ここは後に再設計と実装を行う
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "../Battle.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Explosion.h"
#include "GameLib/GameLib.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

// リソースIDを登録する関数
void EffectManager::RegisterID(EFFECT_TYPE type, int tex_ID, int vtx_ID)
{
	m_EffectResurce[type];
	m_EffectResurce[type].TEX_ID = tex_ID;
	m_EffectResurce[type].VTX_ID = vtx_ID;
}

// エフェクトを作成する関数
void EffectManager::Create(D3DXVECTOR3 pos, EffectManager::EFFECT_TYPE type)
{
	switch(type)
	{
	case EffectManager::EXPLOSION:
		m_Effect.emplace_back(new Explosion(pos, m_EffectResurce[type].TEX_ID, m_EffectResurce[type].VTX_ID));
		break;
	}
}

// コントロール関数
void EffectManager::Control()
{
	if(m_Effect.size() > 0)
	{
		for(auto itr = m_Effect.begin(); itr != m_Effect.end();)
		{
			if((*itr)->Control())
			{
				delete (*itr);
				itr = m_Effect.erase(itr);
				continue;
			}
			++itr;
		}
	}
}

// 描画関数
void EffectManager::Draw()
{
	GameLib::Instance().GetDevice()->SetFVF(USER_VERTEX_FVF);
	if(m_Effect.size() > 0)
	{
		for(auto effect : m_Effect)
		{
			effect->Draw();
		}
	}
}

void EffectManager::ReleaseID()
{
	m_EffectResurce.clear();
}

EffectManager::~EffectManager()
{
	m_EffectResurce.clear();

	for(auto effect : m_Effect)
	{
		delete effect;
	}
	m_Effect.clear();
}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Private functions 
//--------------------------------------------------------------------------------------------------------------------------------------//

EffectManager::EffectManager()
{
}
