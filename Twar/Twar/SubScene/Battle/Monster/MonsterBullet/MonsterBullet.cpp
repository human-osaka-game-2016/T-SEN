/**
* @file		MonsterBullet.cpp
* @brief	MonsterBulletクラス実装
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "Fbx/FbxRelated.h"
#include "MonsterBullet.h"
#include "../../Effect/EffectManager.h"
#include "GameLib/GameLib.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

MonsterBullet::MonsterBullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float radian)
	: m_EffectManager(EffectManager::Instance())
	, m_pModel(pModel)
	, m_Pos(rPos)
	, m_Radian(radian)
	, m_HasVanished(false)
	, m_FireCount(0)
	, m_Angle(D3DXToDegree(radian))
{
}

MonsterBullet::~MonsterBullet()
{
}


