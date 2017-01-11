/**
* @file		Evade.cpp
* @brief    Evadeクラス実装
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "Evade.h"
#include "../../Battle/Radar.h"

//---------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//---------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

const float		CorrectionRange = 200.f;

}

//---------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//---------------------------------------------------------------------------------------------------------------------------------------//

Evade::Evade()
{
}

Evade::~Evade()
{
}

State::STATE_ID Evade::Control(const Ship::STATUS& rStatus)
{
	m_Status = rStatus;

	D3DXVECTOR3 targetPos = Radar::Instance().GetMonsterPos();

	float targetRadian;
	if((targetPos.z - m_Pos.z) >= 0.0f)			// ターゲットのZ座標の位置によって計算方法をかえる
	{
		targetRadian = atan2f((targetPos.x - m_Pos.x), (targetPos.z - m_Pos.z));

	}
	else
	{
		targetRadian = atan2f((targetPos.z - m_Pos.z), (targetPos.x - m_Pos.x));
		targetRadian = D3DXToRadian(m_CorrectionAngle) - targetRadian;
	}

	m_Angle = 360.f - (targetRadian / (3.141592f / 180.f));

	D3DXVECTOR3 vecLength = (m_Pos - targetPos);
	float length = D3DXVec3Length(&vecLength);

	if(length < (m_FiringRange + CorrectionRange))
	{
		m_Pos.x += static_cast<float>(sin(targetRadian) * m_SpeedLimit);
		m_Pos.z += static_cast<float>(cos(targetRadian) * m_SpeedLimit);
	}
	else
	{
		return State::PURSUIT;
	}

	return State::EVADE;
}


