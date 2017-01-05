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

//------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//------------------------------------------------------------------------------------------------------------------------------------//

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

	if(datas.size() == 0)
	{
		D3DXVECTOR3 taegetPos = { 2000.0f, 2000.0f, 2000.0f };
		return taegetPos;
	}

	std::sort(datas.begin(), datas.end(), Radar::CompareLength);

	D3DXVECTOR3 taegetPos = datas[0].pos;
	//datas.clear();
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

//------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//------------------------------------------------------------------------------------------------------------------------------------//

Radar::Radar()
{
}

bool Radar::CompareLength(const ComparisionData& rLeft, const ComparisionData& rRight)
{
	return rLeft.length < rRight.length;
}
