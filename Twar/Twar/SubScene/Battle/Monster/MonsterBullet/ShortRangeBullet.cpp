/**
* @file		ShortRangeBullet.cpp
* @brief	ShortRangeBulletクラス実装
* @autnor	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include <random>
#include "GameLib/GameLib.h"
#include "Fbx/FbxRelated.h"
#include "ShortRangeBullet.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//--------------------------------------------------------------------------------------------------------------------------------------//

/**@todo	ここの乱数テーブルの数値は仮の値*/
namespace
{
	
const float		FiringHeight				= 50.f;				// 弾の発射する高さ
const float		BulletSpeed					= 8.f;				// 弾の速度
const float		Gravity						= -0.25f;			// 重力
const float		PosYMinLimit				= -10.f;			// Y軸における位置座標の最小の限界値
const int		PatternCount				= 15;				// 乱数のパターン数

// 弾の速度の乱数テーブル
const float		SpeedTable[PatternCount] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.0f, 11.f, 12.f, 13.f, 14.f, 15.f };

// 待機時間の乱数テーブル
const int		StanbyTimeTable[PatternCount] = { 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56 };

}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

ShortRangeBullet::ShortRangeBullet(FbxModel* pModel, const D3DXVECTOR3& rPos, float radian)
	: MonsterBullet(pModel, rPos, radian)
	, m_FlyingTimeCount(0)
	, m_StanbyTime(0)
	, m_StanbyTimeCount(0)
{
	m_Pos.y += FiringHeight;
	m_BulletSpeedX = static_cast<float>(cos(m_Radian) * BulletSpeed);
	m_BulletSpeedZ = static_cast<float>(sin(m_Radian) * BulletSpeed);

	std::random_device seed_gen;
	std::mt19937 mt(seed_gen());
	std::uniform_int_distribution<> dist(0, (PatternCount - 1));

	m_BulletSpeedY	= SpeedTable[dist(mt)];
	m_StanbyTime = StanbyTimeTable[dist(mt)];
}

ShortRangeBullet::~ShortRangeBullet()
{
	// モデルのリソース解放はMonsterBulletManagerにて行う
}

// コントロール関数
bool ShortRangeBullet::Control()
{
	if (m_IsHit && m_FireCount >= 10)
	{
		m_HasVanished = true;
		m_IsHit = false;
		m_EffectManager.Create(m_Pos, m_EffectManager.EXPLOSION);
	}
	else if (m_StanbyTime == m_StanbyTimeCount)
	{
		m_IsHit = false;
		m_OldPos = m_Pos;
		m_Pos.x += m_BulletSpeedX;
		m_Pos.z += m_BulletSpeedZ;
		m_Pos.y += (m_BulletSpeedY + Gravity * m_FlyingTimeCount);

		if(m_Pos.y < PosYMinLimit)
		{
			m_HasVanished = true;
		}

		++m_FlyingTimeCount;
	}
	else
	{
		++m_StanbyTimeCount;
	}
	m_FireCount++;
	return m_HasVanished;
}

// 描画関数
void ShortRangeBullet::Draw()
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
}

