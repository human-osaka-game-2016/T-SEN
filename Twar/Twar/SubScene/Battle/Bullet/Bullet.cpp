/**
* @file  Bullet.cpp
* @brief Bulletクラス実装
* @author Matsuda
*/
#include"Bullet.h"
#include"GameLib/GameLib.h"

Bullet::Bullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float angle, D3DXVECTOR3* vec, float bulletSpeed)
	: m_EffectManager(EffectManager::Instance())
	, m_pFbx(pModel)
	, m_Pos(rPos)
	, m_Rotate(angle)
	, m_FireCount(0)
	, m_HasVanished(false)
	, m_pMesh(nullptr)
	, m_FlyingTimeCount(0)
{
	D3DXVec3Normalize(&m_Vector, vec);
	m_BulletSpeedX = m_Vector.x * bulletSpeed;
	m_BulletSpeedY = m_Vector.y * bulletSpeed;
	m_BulletSpeedZ = m_Vector.z * bulletSpeed;
	m_Radian = D3DXToRadian(angle);
}

Bullet::~Bullet()
{
}

bool Bullet::Control()
{
	return false;
}

void Bullet::Draw()
{
}

//void Bullet::PushBack(Data* pData)
//{
//}
//
//Bullet::Data * Bullet::EraseNext(Data* pData)
//{
//	return pData;
//}
//
//void Bullet::Clear()
//{
//}
