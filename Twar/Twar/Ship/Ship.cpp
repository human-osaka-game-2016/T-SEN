#include "Ship.h"


Ship::Ship(D3DXVECTOR3* pos):
m_ObjPos(*pos),
m_pD3Device(GraphicsDevice::GetInstance().GetDevice()),
m_pcameraController(&CameraController::GetInstance())
{
	m_CameraPos.x = m_ObjPos.x;
	m_CameraPos.y = m_ObjPos.y + 50.f;
	m_CameraPos.z = m_ObjPos.z;

	m_LookatPos.x = m_ObjPos.x;
	m_LookatPos.y = m_ObjPos.y;
	m_LookatPos.z = m_ObjPos.z;

	m_Angle = 50.f;

	m_Zoom = false;
}


Ship::~Ship()
{
}

void Ship::Control()
{
}

void Ship::Player()
{
}

void Ship::Ally()
{
}

void Ship::Enemy()
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
	D3DXMatrixMultiply(&matWorld, &matWorld, &m_Rotation);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);


	//	下のやり方で〇速ってのが表現できる
	//	oldは前のフレームのもので前のフレームで行った変換情報も所持している
	/*
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXMATRIX		matPos;							// 移動用行列
	static bool first = true;
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);
	matPos *= matRotate;
	if (first)
	{
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	first = false;
	}
	else
	{
	D3DXMatrixMultiply(&matWorld, &oldWorld, &matPos);
	}

	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);
	oldWorld = matWorld;
	*/
}


void Ship::CameraTransWorld(float radius)
{
//	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXVECTOR3		cameraPos(0.f, 0.f, -radius);
//	D3DXMATRIX		matPos;							// 移動用行列
//	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXVec3TransformCoord(&cameraPos, &cameraPos, &m_CameraRotation);
	D3DXVec3Add(&cameraPos, &cameraPos, &m_CameraPos);
	m_CameraPos.x = cameraPos.x;
	m_CameraPos.z = cameraPos.z;
//	D3DXMatrixTranslation(&matPos, vecTarget.x, vecTarget.y, vecTarget.z);
//	D3DXMatrixMultiply(&matWorld, &matWorld, rotation);
//	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
//	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3		lookatPos(0.f, 0.f, radius);
	D3DXVec3TransformCoord(&lookatPos, &lookatPos, &m_CameraRotation);
	D3DXVec3Add(&lookatPos, &lookatPos, &m_LookatPos);
	m_LookatPos.x = lookatPos.x;
	m_LookatPos.z = lookatPos.z;
}