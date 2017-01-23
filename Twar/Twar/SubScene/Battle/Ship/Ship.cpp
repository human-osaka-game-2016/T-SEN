/**
	@file ShipManager.cpp
	@brief ShipManagerクラスcpp
	@author kawaguchi
*/

#include "Ship.h"
#include "GameLib/GameLib.h"
#include "../CameraController/CameraController.h"
#include "Fbx/FbxModel.h"

const float	Ship::m_LimitArrivalFlame	= 500.f;
const float	Ship::m_DecelerationSpeed	= 0.002f;
const float	Ship::m_PitchSpeed			= 0.025f;
const float	Ship::m_PitchUpperLimit		= -6.f;
const float	Ship::m_PitchLowerLimit		= -2.f;
const float Ship::m_CameraHeight		= 50.f;
const float	Ship::m_NormalAngle			= 50.f;
const float	Ship::m_ZoomAngle			= 10.f;

Ship::Ship(D3DXVECTOR3* pos, STATUS status)
	: m_pGameLib(GameLib::Instance())
	, m_pFbx(nullptr)
	, m_ObjPos(*pos)
	, m_pcameraController(CameraController::GetInstance())
	, m_Status(status)
	, m_CameraPos({ pos->x, pos->y + m_CameraHeight, pos->z })
	, m_LookatPos({ pos->x, pos->y + m_CameraHeight, pos->z })
	, m_Angle(m_NormalAngle)
	, m_IsZoom(false)
	, m_IsUp(false)
{
}


Ship::~Ship()
{
}

void Ship::Control()
{
}

void Ship::ControlPlayer()
{
}

void Ship::ControlAlly()
{
}

void Ship::ControlEnemy()
{
}

void Ship::Draw()
{
}

void Ship::TransWorld()
{
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXMATRIX		matPos;							// 移動用行列
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXMatrixTranslation(&matPos, m_ObjPos.x, m_ObjPos.y, m_ObjPos.z);
	D3DXMatrixMultiply(&matWorld, &m_Slope, &m_Rotation);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	m_pGameLib.GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
}


void Ship::CameraTransWorld(float radius)
{
	D3DXVECTOR3		cameraPos(0.f, 0.f, -radius);
	D3DXVec3TransformCoord(&cameraPos, &cameraPos, &m_CameraRotation);
	D3DXVec3Add(&cameraPos, &cameraPos, &m_CameraPos);
	m_CameraPos.x = cameraPos.x;
	m_CameraPos.z = cameraPos.z;

	D3DXVECTOR3		lookatPos(0.f, 0.f, radius);
	D3DXVec3TransformCoord(&lookatPos, &lookatPos, &m_CameraRotation);
	D3DXVec3Add(&lookatPos, &lookatPos, &m_LookatPos);
	m_LookatPos.x = lookatPos.x;
	m_LookatPos.z = lookatPos.z;
}

