/**
* @file		LongRangeBullet.cpp
* @brief	LongRangeBulletクラス実装
* @author	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "Fbx/FbxRelated.h"
#include "../../Collision/Collision.h"
#include "../../Effect/EffectManager.h"
#include "LongRangeBullet.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//-------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

const float		FiringHeight		= 50.f;				// 弾の発射する高さ
const float		BulletSpeed			= 3.0f;				// 弾の速度
const float		BulletRange			= 800.f;			// 弾の高さを保ってられる範囲.この範囲を過ぎると徐々に降下していく
const float		DescendingSpeed		= 1.0f;				// 弾の降下速度(弾の射程範囲を超える場合び落下するときの速度)
const float		PosYMinLimit		= -50.f;			// Y軸における位置座標の最小の限界値
const float		RollingSpeed		= 0.5f;				// 弾の回転速度(回転角度)
const float		ScaleVal			= 5.0f;				// 弾の大きさの倍率

}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

LongRangeBullet::LongRangeBullet(FbxModel* pModel, const D3DXVECTOR3& rPos, float radian)
	: MonsterBullet(pModel, rPos, radian)
	, m_FlyingDistanceCount({0.0f, 0.0f, 0.0f})
	, m_RollingAngle(0.0f)
	, m_IsWithinRange(true)
{
	m_pCollision = new Collision(30.f, Collision::MONSTER);
	m_Pos.y += FiringHeight;
	m_BulletSpeedX = static_cast<float>(cos(m_Radian) * BulletSpeed);
	m_BulletSpeedZ = static_cast<float>(sin(m_Radian) * BulletSpeed);
}

LongRangeBullet::~LongRangeBullet()
{
	delete m_pCollision;
	// モデルのリソース解放はMonsterBulletManagerにて行う
}

// コントロール関数
bool LongRangeBullet::Control()
{
	if(m_pCollision->InformCollision())
	{
		EffectManager::Instance().Create(m_Pos, EffectManager::EXPLOSION);
		m_HasVanished = true;
		return m_HasVanished;
	}

	if(m_IsWithinRange)
	{
		m_Pos.x += m_BulletSpeedX;
		m_Pos.z += m_BulletSpeedZ;
		m_FlyingDistanceCount.x += m_BulletSpeedX;
		m_FlyingDistanceCount.z += m_BulletSpeedZ;

		// 弾が範囲内にあるかチェック
		if(m_FlyingDistanceCount.x >  BulletRange || m_FlyingDistanceCount.x < -BulletRange ||
			m_FlyingDistanceCount.z > BulletRange || m_FlyingDistanceCount.z < -BulletRange)
		{
			m_IsWithinRange = false;
		}
	}
	else
	{
		m_Pos.x += m_BulletSpeedX;
		m_Pos.z += m_BulletSpeedZ;
		m_Pos.y -= DescendingSpeed;

		if(m_Pos.y < PosYMinLimit)
		{
			m_HasVanished = true;
		}
	}

	// 弾の回転処理
	m_RollingAngle += RollingSpeed;
	if(m_RollingAngle > 360.f)
	{ 
		m_RollingAngle -= 360.f;		// 正規化
	}

	m_pCollision->SetData(m_Pos);

	return m_HasVanished;
}

// 描画関数
void LongRangeBullet::Draw()
{
	D3DXMatrixIdentity(&m_MatWorld);	// 単位行列

	// 拡大
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, ScaleVal, ScaleVal, ScaleVal);
	matScale._41 = 0.0f;
	matScale._42 = 0.0f;
	matScale._43 = 0.0f;
	m_MatWorld *= matScale;

	// 回転
	D3DXMATRIX	matBank;
	D3DXMatrixRotationZ(&matBank, D3DXToRadian(m_RollingAngle));
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matBank);

	D3DXMATRIX	matHeading;												
	D3DXMatrixRotationY(&matHeading, m_Radian);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matHeading);

	// 移動
	D3DXMATRIX	matPosition;	// 位置座標行列
	D3DXMatrixTranslation(&matPosition, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matPosition);
	GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &m_MatWorld);
	m_pModel->DrawFbx();
}
