﻿/**
* @file		MonsterBullet.cpp
* @brief	MonsterBulletクラス実装
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "Fbx/FbxRelated.h"
#include "MonsterBullet.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

MonsterBullet::MonsterBullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float radian)
	: m_pModel(pModel)
	, m_Pos(rPos)
	, m_Radian(radian)
	, m_HasVanished(false)
{
}

MonsterBullet::~MonsterBullet()
{
}


