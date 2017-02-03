/**
* @file		Radar.cpp
* @brief	Radarクラス実装
* @author	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include <algorithm>
#include "Radar.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//-------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

const	int		PlayerAttackCountLimit = 2;		// プレイヤーに攻撃をされたカウントの限界値

}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

D3DXVECTOR3 Radar::GetNearShipPos(const D3DXVECTOR3& rPos)
{
	std::vector<ComparisionData> datas;
	for(auto itr = m_ShipPos.begin(); itr != m_ShipPos.end(); ++itr)
	{
		D3DXVECTOR3 vecLength = (rPos - (*itr));
		float length = D3DXVec3Length(&vecLength);

		ComparisionData data;

		data.pos = (*itr);
		data.length = length;
		datas.push_back(data);
	}

	if(datas.empty())
	{
		// 何もデータがない場合は適当な値を代入してかえす
		D3DXVECTOR3 taegetPos = { 2000.0f, 2000.0f, 2000.0f };
		return taegetPos;
	}

	std::sort(datas.begin(), datas.end(), Radar::CompareLength);

	D3DXVECTOR3 taegetPos = datas[0].pos;
	datas.clear();
	return taegetPos;
}

D3DXVECTOR3 Radar::GetAIAttackTargetPos(const D3DXVECTOR3& rPos, int playerAttackedCount)
{
	if(playerAttackedCount < PlayerAttackCountLimit)
	{
		return  GetMonsterPos();
	}
	else
	{
		// 下記の処理を行う 
	}

	 
	D3DXVECTOR3 MonstrerVecLength = (rPos - GetMonsterPos());
	float ToMonsterlength = D3DXVec3Length(&MonstrerVecLength);

	// 現在の仕様ではm_ShipPos[0]はプレイヤーの座標
	D3DXVECTOR3 PlayerVecLength = (rPos - m_ShipPos[0]);
	float ToPlayerlength = D3DXVec3Length(&PlayerVecLength);

	
	D3DXVECTOR3 taegetPos = {0.0f, 0.0f, 0.0f};

	D3DXVECTOR3 taegetPos;
	return taegetPos;
}

void Radar::SetShipPos(const D3DXVECTOR3& rPos)
{
	m_ShipPos.push_back(rPos);
}

void Radar::SetMonsterPos(const D3DXVECTOR3& rPos)
{
	m_MonsterPos = rPos;
}

void Radar::ClearData()
{
	m_ShipPos.clear();
}

Radar::~Radar()
{
}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//-------------------------------------------------------------------------------------------------------------------------------------//

Radar::Radar()
{
}

bool Radar::CompareLength(const ComparisionData& rLeft, const ComparisionData& rRight)
{
	return rLeft.length < rRight.length;
}
