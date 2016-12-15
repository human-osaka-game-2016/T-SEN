/**
* @file		Monster.cpp
* @brief	Monsterクラス実装
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include <random>
#include "GameLib/GameLib.h"
#include "Fbx/FbxRelated.h"
#include "Monster.h"
#include "../Collision/Collision.h"
#include "../Effect/EffectManager.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//--------------------------------------------------------------------------------------------------------------------------------------//

// 数字は仮置き 時間は60FPSで計算
namespace
{

const float			attitudeAngle = -90.f;						// ゴーレムの姿勢をたたせる為の角度
const float			scailVal = 2.0f;							// 拡大率
const float			searchRange = 600.f;						// 索敵範囲
const float			shortAttackRange = 600.f;					// 近距離攻撃範囲
const float			longAttackRange = 3000.f;					// 遠距離攻撃範囲
const int			nonAttackTime = 3600;						// 攻撃状態において攻撃していない時間
const int			moveTime = 300;								// 移動時間
const float			PosYMinLimit = -340.f;						// y軸における位置座標の下の限界
const float			upDownSpeed = 1.0f;							// 上下運動における速度
const int			fadeOutTime = 300;							// HPが0になった後、消えていく時間
const int			posNum = 3;									// モンスター位置座標の数

// 出現位置テーブル
const D3DXVECTOR3	appearancePos[posNum] = {
	{0.f, 0.0f, 0.f},
	{0.f, 0.0f, 0.f},
	{0.f, 0.0f, 0.f}
};

}

//----------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//----------------------------------------------------------------------------------------------------------------------------------------//

Monster::Monster(FbxModel* model)
	: m_Angle(180.0f)
	, m_pModel(model)
	, m_Collision(new Collision(100.f))
	, m_Status({5,0,300})
	, m_State(Monster::STANDBY)
	, m_AttackInterValCount(0)
	, m_NonAttackTimeCount(0)
	, m_MoveTimeCount(0)			
	, m_IsMoving(false)					
	, m_FadeOutTimeCount(0)
	, m_HasDisappeared(false)
{
	std::random_device seed_gen;
	std::mt19937 mt(seed_gen());
	std::uniform_int_distribution<> dist(0, ( posNum - 1 ));
	m_Pos = appearancePos[dist(mt)];
}

Monster::~Monster()
{
	delete m_Collision;
	// リソース(モデル)解放はMonsterManagerにて行う
}

bool Monster::Control()
{
	JudgeColllision();

	switch(m_State)
	{
	case STANDBY:
		SearchTarget();
		m_Collision->SetData(m_Pos);
		break;

	case COMBAT:
		AttackTarget();
		break;

	case MOVING:
		Move();
		break;

	case DEATH:
		Fall();
		//D3DXVECTOR3 effectPos = m_Pos;
		//effectPos.z -= 200.f;
		//EffectManager::Instance().Create(effectPos, EffectManager::EXPLOSION);
		if(m_Pos.y <= PosYMinLimit)
		{
			m_HasDisappeared = true;
		}
		
		break;
	}

	return m_HasDisappeared;
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
	if(m_Collision->InformCollision())
	{
		m_Status.Hp -= 1;
		if(m_Status.Hp <= 0)
		{
			m_State = DEATH;
		}
	}
}

void Monster::SearchTarget()
{

}

void Monster::AttackTarget()
{

}

void Monster::Move()
{
	if(m_IsMoving)
	{
		if(m_MoveTimeCount == moveTime)
		{
			Rise();
		}
		else
		{
			m_MoveTimeCount++;
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
		m_IsMoving = true;

		D3DXVECTOR3  pos = {0.0f,0.0f,0.0f};
		std::random_device seed_gen;
		std::mt19937 mt(seed_gen());
		std::uniform_int_distribution<> dist(0, ( posNum - 1 ));

		while(m_Pos.x == pos.x && m_Pos.z == pos.z)
		{
			pos = appearancePos[dist(mt)];
		}
		// ここで次の位置座標をいれる
		m_Pos.x = pos.x;
		m_Pos.z = pos.z;
	}
	else
	{
		m_Pos.y -= upDownSpeed;
	}
}

void Monster::Rise()
{
	if(m_Pos.y == 0.0f)		// 0.0fはy座標における
	{
		m_IsMoving = false;
		m_State = Monster::STANDBY;
		m_MoveTimeCount = 0;
		return;
	}

	m_Pos.y += upDownSpeed;
}


void Monster::ControlAttitude()
{
	D3DXMATRIX		matPicth;							// 移動用行列x
	D3DXMATRIX		matHeading;							// 移動用行列y
	D3DXMATRIX		matRotation;						// 回転行列

	D3DXMatrixIdentity(&matRotation);
	MoveParallel(( 0 - m_Pos.x ), ( 0 - m_Pos.y ), ( 0 - m_Pos.z ));
	
	// 拡大
	D3DXMATRIX matScail;
	D3DXMatrixScaling(&matScail, scailVal, scailVal, scailVal);
	m_MatWorld *= matScail;

	// 回転行列
	D3DXMatrixRotationX(&matPicth, D3DXToRadian(attitudeAngle));
	D3DXMatrixMultiply(&matRotation, &matRotation, &matPicth);

	D3DXMatrixRotationY(&matHeading, D3DXToRadian(m_Angle));
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
