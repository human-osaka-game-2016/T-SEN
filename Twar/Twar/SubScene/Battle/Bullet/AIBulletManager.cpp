//==================================================================================================================================//
//!< @file		AttackTarget.cpp
//!< @brief		AttackTargetクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <math.h>
#include "Fbx/FbxRelated.h"
#include "AIBulletManager.h"
#include "AIBullet.h"

//--------------------------------------------------------------------------------------------------------------//
//Static variable
//--------------------------------------------------------------------------------------------------------------//

AIBulletManager*	AIBulletManager::m_pBulletManager = nullptr;

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

void AIBulletManager::Control()
{
	for(auto& itr = m_pBullets.begin(); itr != m_pBullets.end();)
	{
		if((*itr)->Control())
		{
			delete (*itr);
			itr = m_pBullets.erase(itr);
			continue;
		}
		++itr;
	}
}

void AIBulletManager::Draw()
{
	for(auto& itr = m_pBullets.begin(); itr != m_pBullets.end();)
	{
		(*itr)->Draw();
		++itr;
	}
}

void AIBulletManager::CreateBullet(const D3DXVECTOR3& rPos, float angle)
{
//	float radian = D3DXToRadian(angle);
	m_pBullets.push_back(new AIBullet(m_pBulletModel->m_pModel, rPos, angle));
}

//--------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------//

AIBulletManager::AIBulletManager()
	: m_pBulletModel(new FbxRelated())
{
	// モデルデータ読み込み
	/**@todo 2016/12/23現在モデルデータは仮置き*/
	if(!m_pBulletModel->LoadFbx("fbx/tama_0.FBX"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "AI弾のFBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
}

AIBulletManager::~AIBulletManager()
{
	for(auto pBullet : m_pBullets)
	{
		delete pBullet;
	}

	delete m_pBulletModel;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
