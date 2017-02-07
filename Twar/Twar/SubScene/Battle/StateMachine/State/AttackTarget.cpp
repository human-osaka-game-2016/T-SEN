//==================================================================================================================================//
//!< @file		AttackTarget.cpp
//!< @brief		AttackTargetクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <random>
#include "AttackTarget.h"
#include "../../Radar/Radar.h"
#include "../ShipStateManager.h"
#include "../../Bullet/AIBulletManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const		int		BulletInterval	   = 300;				// 弾の発射間隔
const		float	PossibleAttackPosY = -3.0f;				// 攻撃可能なターゲットのY座標値

}

//--------------------------------------------------------------------------------------------------------------//
//Static variable
//--------------------------------------------------------------------------------------------------------------//

AttackTarget*	 AttackTarget:: m_pAttackTarget = nullptr;

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

void AttackTarget::Enter(Ship* pShip)
{
	// すぐに攻撃が行えるようにする
	pShip->SetBulletIntervalCount(BulletInterval);

	const D3DXVECTOR3& targetPos = Radar::Instance().GetMonsterPos();
	//const D3DXVECTOR3& targetPos = Radar::Instance().GetAIAttackTargetPos();
	const D3DXVECTOR3& shipPos = pShip->GetObjPos();
	// ターゲットへの方向を求める
	float targetAngle = 0.0f;
	float targetRadian = 0.0f;
	targetRadian = atan2f((targetPos.x - shipPos.x), (targetPos.z - shipPos.z));
	targetAngle = D3DXToDegree(targetRadian);
	pShip->SetTargetAngle(targetAngle);
}

void AttackTarget::Execute(Ship* pShip)
{
	// ランダムイベント処理
	{
		std::random_device seed_gen;
		std::mt19937 mt(seed_gen());
		std::uniform_int_distribution<> dist(0, 99);
		int randamNum = dist(mt);

		/**@todo 後で修正する*/
		// ニ割の確立で回避行動をとる
		if(randamNum < 20)
		{
			pShip->GetStateMachine()->SetCurrntState(ShipStateManager::GetShipState(ShipStateManager::AVOID_OBJECT));
		}

	}

	const D3DXVECTOR3& currentTargetPos = Radar::Instance().GetMonsterPos();
	// ターゲットが移動している場合、移動状態に切り替える
	if(pShip->GetTargetPos().x != currentTargetPos.x
	   && pShip->GetTargetPos().z != currentTargetPos.z)
	{
		pShip->GetStateMachine()->ChangeState(ShipStateManager::GetShipState(ShipStateManager::TURNING_AROUND));
		return;
	}
	else
	{
		// 下記の攻撃関連処理を行う
	}

	// 攻撃を行う
	int bulletIntervalCount = pShip->GetBulletIntervalCount();
	if(bulletIntervalCount >= BulletInterval && currentTargetPos.y >= PossibleAttackPosY)
	{
		// 弾生成
		AIBulletManager::Instance()->CreateBullet(pShip->GetObjPos(), pShip->GetToTargetAngle());
		bulletIntervalCount = 0;
	}
	else
	{
		++bulletIntervalCount;
	}

	D3DXVECTOR3 vecAxisZ = { 0.0f, 0.0f, 1.0f };

	D3DXMATRIX		matRotation;						// 回転行列
	D3DXMatrixRotationY(&matRotation, D3DXToRadian(pShip->GetRotate()));
	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &matRotation);

	D3DXVECTOR3 pos = pShip->GetObjPos();
	float		speed = pShip->GetSpeedLimit();

	pos += vecAxisZ * speed;
	pShip->SetObjPos(pos);
	pShip->SetBulletIntervalCount(bulletIntervalCount);
}

void AttackTarget::Exit(Ship* pShip)
{
	// 空処理
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
