//==================================================================================================================================//
//!< @file		AIBullet.h
//!< @brief		AIBulletクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "AIBullet.h"
#include "GameLib/GameLib.h"
#include "Fbx/FbxRelated.h"
#include "../Effect/EffectManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

	const float		BulletSpeed = 8.f;				// 弾の速度
	const float		Gravity = -0.25f;				// 重力
	const float		PosYMinLimit = -10.f;			// Y軸における位置座標の最小の限界値

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

AIBullet::AIBullet(FbxModel* pModel, const D3DXVECTOR3& rPos, float angle)
	: m_EffectManager(EffectManager::Instance())
	, m_pModel(pModel)
	, m_Pos(rPos)
	, m_Angle(angle)
	, m_FlyingTimeCount(0)
	, m_HasVanished(false)
	, m_pMesh(nullptr)
	, m_FireCount(0)
{
	m_Radian = D3DXToRadian(angle);
	m_BulletSpeedX = static_cast<float>(sin(m_Radian) * BulletSpeed);
	m_BulletSpeedZ = static_cast<float>(cos(m_Radian) * BulletSpeed);
	m_BulletSpeedY = BulletSpeed;
}

AIBullet::~AIBullet()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
	}
}

bool AIBullet::Control()
{
	if (m_IsHit && m_FireCount >= 10)
	{
		m_HasVanished = true;
		m_IsHit = false;
		m_EffectManager.Create(m_Pos, m_EffectManager.EXPLOSION);
	}
	else if (m_Pos.y > PosYMinLimit)
	{
		m_IsHit = false;
		m_OldPos = m_Pos;
		m_Pos.x += m_BulletSpeedX;
		m_Pos.z += m_BulletSpeedZ;
		m_Pos.y += (m_BulletSpeedY + Gravity * m_FlyingTimeCount);

		if (m_Pos.y < PosYMinLimit)
		{
			m_HasVanished = true;
		}

		++m_FlyingTimeCount;
	}
	else
	{
		m_HasVanished = true;
	}
	m_FireCount++;

	return m_HasVanished;
}

void AIBullet::Draw()
{
	D3DXMatrixIdentity(&m_MatWorld);

	// 回転
	D3DXMATRIX			matHeading;
	D3DXMatrixRotationY(&matHeading, m_Radian);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matHeading);

	// 移動
	D3DXMATRIX			matPosition;	// 位置座標行列
	D3DXMatrixTranslation(&matPosition, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matPosition);
	GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &m_MatWorld);
	m_pModel->DrawFbx();
	//D3DXCreateSphere(GameLib::Instance().GetDevice(), 7, 64, 32, &m_pMesh, nullptr);
	//m_pMesh->DrawSubset(0);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
