/**
* @file		Monster.cpp
* @brief	Monsterクラス実装
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include <random>
#include <math.h>
#include "GameLib/GameLib.h"
#include "Fbx/FbxRelated.h"
#include "../Collision/Collision.h"
#include "Monster.h"
#include "MonsterBullet/MonsterBulletManager.h"
#include "../Effect/EffectManager.h"
#include "../Battle/Radar.h"
#include "../Battle/BattleStateManager.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//--------------------------------------------------------------------------------------------------------------------------------------//

// 数字は仮置き 時間は60FPSで計算
namespace
{

const float			AttitudeAngle		= -90.f;					// ゴーレムの姿勢をたたせる為の角度
const float			CorrectionAngle		= 90.f;						// 計算補正角度
const float			ScaleVal			= 2.0f;						// 拡大率
const float			SearchRange			= 600.f;					// 索敵範囲
const float			ShortAttackRange	= 500.f;					// 近距離攻撃範囲
const float			LongAttackRange		= 900.f;					// 遠距離攻撃範囲
const int			NonAttackTime		= 3600;						// 攻撃状態において攻撃していない時間
const int			MoveTime			= 300;						// 移動時間
const float			PosYMinLimit		= -360.f;					// y軸における位置座標の下の限界
const float			UpDownSpeed			= 1.0f;						// 上下運動における速度
const float			RollingSpeed		= 0.0625f;					// 回転速度
const int			PosCount			= 3;						// モンスター位置座標の数

// 出現位置テーブル
const D3DXVECTOR3	PositionTable[PosCount] = {
	{ 100.f, 0.0f,  100.f},
	{-800.f, 0.0f,  800.f},
	{ 800.f, 0.0f,  800.f}
};

}

//----------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//----------------------------------------------------------------------------------------------------------------------------------------//

Monster::Monster(FbxModel* pModel, MonsterBulletManager* pBulletManager)
	: m_Radian(D3DXToRadian(180.f))
	, m_pModel(pModel)
	, m_Status({20,0,300})
	, m_State(Monster::STANDBY)
	, m_SearchRange(SearchRange)
	, m_RollingSpeed(0.0f)
	, m_TargetPos({0.0f, 0.0f, 0.0f})
	, m_AttackInterValCount(0)
	, m_NonAttackTimeCount(0)
	, m_MoveTimeCount(0)			
	, m_HasMoved(false)
	, m_HasVanished(false)
	, m_pBulletManager(pBulletManager)
	, m_pCollision(new Collision(100.f, Collision::MONSTER))
{
	std::random_device seed_gen;
	std::mt19937 mt(seed_gen());
	std::uniform_int_distribution<> dist(0, ( PosCount- 1 ));
	m_Pos = PositionTable[dist(mt)];
	Radar::Instance().SetMonsterPos(m_Pos);
	BattleStateManager::Instance().SetMonsterHP(m_Status.Hp);
}

Monster::~Monster()
{
	delete m_pCollision;
	// リソース(モデル)解放はMonsterManagerにて行う
}

bool Monster::Control()
{
	switch(m_State)
	{
	case STANDBY:
		JudgeColllision();
		SearchTarget();
		if(m_SearchRange == LongAttackRange)
		{
			m_State = ROTATION;
		}
		m_pCollision->SetData(m_Pos);
		break;

	case ROTATION:
		JudgeColllision();
		Rotate();
		m_pCollision->SetData(m_Pos);
		break;

	case COMBAT:
		JudgeColllision();
		AttackTarget();
		m_pCollision->SetData(m_Pos);
		break;

	case MOVING:
		Move();
		break;

	case DEATH:
		FadeOut();
		break;
	}

	Radar::Instance().SetMonsterPos(m_Pos);
	BattleStateManager::Instance().SetMonsterHP(m_Status.Hp);

	return m_HasVanished;
}

void Monster::Draw()
{
	D3DXMATRIX		matPosition;							// 移動用行列
	D3DXMatrixIdentity(&m_MatWorld);						// 単位行列
	D3DXMatrixTranslation(&matPosition, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matPosition);
	ControlAttitude();
	GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &m_MatWorld);
	m_pModel->DrawFbx();
}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------------------------------//

void Monster::JudgeColllision()
{
	// 衝突判定が入る予定
	if(m_pCollision->InformCollision())
	{
		m_Status.Hp -= 1;
		if(m_Status.Hp <= 0)
		{
			m_State = DEATH;
		}
		else if(m_Status.Hp % 10 == 0)
		{
			m_State = MOVING;
		}
	}
}

void Monster::SearchTarget()
{
	// ターゲットの座標を手に入れる部分が実装予定
	m_TargetPos = Radar::Instance().GetNearShipPos(m_Pos);

	D3DXVECTOR3 vecLength = (m_Pos - m_TargetPos);
	float length = D3DXVec3Length(&vecLength);
	if(length <= m_SearchRange)
	{
		if((m_TargetPos.z - m_Pos.z) >= 0.0f)			// ターゲットのZ座標の位置によって計算方法をかえる
		{
			float targetAngle = atan2f((m_TargetPos.x - m_Pos.x), (m_TargetPos.z - m_Pos.z));
			m_TargetRadian = targetAngle;
		}
		else
		{
			float targetAngle = atan2f((m_TargetPos.z - m_Pos.z), (m_TargetPos.x - m_Pos.x));
			m_TargetRadian = D3DXToRadian(CorrectionAngle) - targetAngle;
		}
		
		m_RadianDifference = (m_Radian - m_TargetRadian);
		if(m_RadianDifference > 0.0f)
		{
			if(m_RadianDifference < D3DXToRadian(180.0f))
			{
				m_RollingSpeed = -RollingSpeed;
			}
			else
			{
				m_RollingSpeed = RollingSpeed;
			}
		}
		else
		{
			if(m_RadianDifference > D3DXToRadian(-180.0f))
			{
				m_RollingSpeed = RollingSpeed;
			}
			else
			{
				m_RollingSpeed = -RollingSpeed;
			}
		}
		// 索敵範囲を更新する
		m_SearchRange = LongAttackRange;
	}
	
}

void Monster::Rotate()
{
	if(m_RollingSpeed > 0.0f)
	{
		if(m_Radian >= m_TargetRadian)
		{
			if(m_AttackInterValCount == 0)
			{
				m_Radian = m_TargetRadian;
				m_State = COMBAT;
			}
			else
			{
				if((m_Radian - m_TargetRadian) > m_RollingSpeed)
				{
					SearchTarget();
				}
			}
		}
		else
		{
			m_Radian += m_RollingSpeed;
		}
	}
	else
	{
		if(m_Radian <= m_TargetRadian)
		{
			if(m_AttackInterValCount == 0)
			{
				m_Radian = m_TargetRadian;
				m_State = COMBAT;
			}
			else
			{
				if((m_Radian - m_TargetRadian) <= m_RollingSpeed)
				{
					SearchTarget();
				}
			}
		}
		else
		{
			m_Radian += m_RollingSpeed;
		}
	}

	// 正規化
	/**@todo ここの条件式は直したい*/
	if(m_Radian > D3DXToRadian(180.0f) && m_RollingSpeed > 0.0f && m_RadianDifference > 0.0f)
	{
		m_Radian -= ((D3DXToRadian(180.0f)) * 2.0f);
	}
	else if(m_Radian < D3DXToRadian(-180.0f) && m_RollingSpeed < 0.0f && m_RadianDifference <= 0.0f)
	{
		m_Radian += ((D3DXToRadian(180.0f)) * 2.0f);
	}

	if(m_AttackInterValCount != 0)
	{
		--m_AttackInterValCount;
	}
}

void Monster::AttackTarget()
{
	if(m_AttackInterValCount == 0)
	{
		D3DXVECTOR3 vecLength = (m_Pos - m_TargetPos);
		float length = D3DXVec3Length(&vecLength);

		if(length <= ShortAttackRange)
		{
			m_pBulletManager->CreateShortRangeBullet(m_Pos);
			m_AttackInterValCount = m_Status.AttackInteval;
			m_NonAttackTimeCount = 0;
		}
		else if(length <= LongAttackRange)
		{
			float radian = 0.0f;
			if((m_TargetPos.z - m_Pos.z) > 0.0f)
			{
				radian = m_Radian;
			}
			else
			{
				radian = D3DXToRadian(CorrectionAngle) - m_Radian;
			}

			m_pBulletManager->CreateLongeRangeBullet(m_Pos,radian);
			m_AttackInterValCount = m_Status.AttackInteval;
			m_NonAttackTimeCount = 0;
		}
		else
		{
			++m_NonAttackTimeCount;
			if(m_NonAttackTimeCount == NonAttackTime)
			{
				m_State = STANDBY;
				m_SearchRange = SearchRange;
				m_NonAttackTimeCount = 0;
			}
		}
	}
	else
	{
		SearchTarget();
		if(RollingSpeed > (m_Radian - m_TargetRadian) || (m_Radian - m_TargetRadian) > -RollingSpeed)
		{
			m_State = ROTATION;
		}
		--m_AttackInterValCount;
	}
}

void Monster::Move()
{
	if(m_HasMoved)
	{
		if(m_MoveTimeCount == MoveTime)
		{
			Rise();
		}
		else
		{
			++m_MoveTimeCount;
		}
	}
	else
	{
		Fall();
	}
}

void Monster::Fall()
{
	if(m_Pos.y == PosYMinLimit)
	{
		m_HasMoved = true;

		D3DXVECTOR3  pos = {0.0f,0.0f,0.0f};
		std::random_device seed_gen;
		std::mt19937 mt(seed_gen());
		std::uniform_int_distribution<> dist(0, ( PosCount - 1 ));

		while(m_Pos.x == pos.x && m_Pos.z == pos.z)
		{
			pos = PositionTable[dist(mt)];
		}
		// ここで次の位置座標をいれる
		m_Pos.x = pos.x;
		m_Pos.z = pos.z;
	}
	else
	{
		m_Pos.y -= UpDownSpeed;
	}
}

void Monster::Rise()
{
	if(m_Pos.y == 0.0f)		
	{
		m_HasMoved = false;
		m_State = Monster::STANDBY;
		m_SearchRange = SearchRange;
		m_MoveTimeCount = 0;
		m_pCollision->SetData(m_Pos);
		return;
	}

	m_Pos.y += UpDownSpeed;
}

void Monster::FadeOut()
{
	m_Pos.y -= UpDownSpeed;
	if(m_Pos.y == PosYMinLimit)
	{
		m_HasVanished = true;
	}
}

// Monsterの姿勢制御を行う関数
void Monster::ControlAttitude()
{
	D3DXMATRIX		matPicth;							// 移動用行列x
	D3DXMATRIX		matHeading;							// 移動用行列y
	D3DXMATRIX		matRotation;						// 回転行列

	D3DXMatrixIdentity(&matRotation);
	MoveParallel(( 0 - m_Pos.x ), ( 0 - m_Pos.y ), ( 0 - m_Pos.z ));
	
	// 拡大
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, ScaleVal, ScaleVal, ScaleVal);
	m_MatWorld *= matScale;

	// 回転行列
	D3DXMatrixRotationX(&matPicth, D3DXToRadian(AttitudeAngle));
	D3DXMatrixMultiply(&matRotation, &matRotation, &matPicth);

	D3DXMatrixRotationY(&matHeading, m_Radian);
	D3DXMatrixMultiply(&matRotation, &matRotation, &matHeading);

	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matRotation);
	MoveParallel(m_Pos.x, m_Pos.y, m_Pos.z);
}

void Monster::MoveParallel(float x, float y, float z)
{
	D3DXMATRIX moveMatrix;						// 移動量の行列
	D3DXMatrixIdentity(&moveMatrix);
	D3DXMatrixTranslation(&moveMatrix, x, y, z);
	m_MatWorld *= moveMatrix;					// 移動
}
